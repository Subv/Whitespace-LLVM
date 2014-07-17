#include "Statements.h"
#include "Whitespace.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include <sstream>

using namespace llvm;

static std::string tostring(int64_t value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

void PushStatement::CodeGen(Whitespace* whitespace)
{
    whitespace->PushStack(whitespace->GetBuilder()->getInt64(_number));
}

void DuplicateTopStatement::CodeGen(Whitespace* whitespace)
{
    Value* duplicate = whitespace->TopStack();
    whitespace->PushStack(duplicate);
}

void CopyStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}

void SwapStatement::CodeGen(Whitespace* whitespace)
{
    Value* first = whitespace->TopStack();
    whitespace->PopStack();
    Value* second = whitespace->TopStack();
    whitespace->PopStack();

    whitespace->PushStack(first);
    whitespace->PushStack(second);
}

void DiscardTopStatement::CodeGen(Whitespace* whitespace)
{
    whitespace->PopStack();
}

void SlideStatement::CodeGen(Whitespace* whitespace)
{
    // TODO: I am not sure if this is correct
    // Definition: 	Slide n items off the stack, keeping the top item
    Value* top = whitespace->TopStack();

    for (int i = 0; i <= _number; ++i)
        whitespace->PopStack();

    whitespace->PushStack(top);
}

void AdditionStatement::CodeGen(Whitespace* whitespace)
{
    Value* rhs = whitespace->TopStack();
    whitespace->PopStack();
    Value* lhs = whitespace->TopStack();
    whitespace->PopStack();

    Value* result = whitespace->GetBuilder()->CreateAdd(lhs, rhs, "AddStatement");
    whitespace->PushStack(result);
}

void SubstractionStatement::CodeGen(Whitespace* whitespace)
{
    Value* rhs = whitespace->TopStack();
    whitespace->PopStack();
    Value* lhs = whitespace->TopStack();
    whitespace->PopStack();

    Value* result = whitespace->GetBuilder()->CreateSub(lhs, rhs, "SubStatement");
    whitespace->PushStack(result);
}

void MultiplicationStatement::CodeGen(Whitespace* whitespace)
{
    Value* rhs = whitespace->TopStack();
    whitespace->PopStack();
    Value* lhs = whitespace->TopStack();
    whitespace->PopStack();

    Value* result = whitespace->GetBuilder()->CreateMul(lhs, rhs, "MulStatement");
    whitespace->PushStack(result);
}

void IntegerDivisionStatement::CodeGen(Whitespace* whitespace)
{
    Value* rhs = whitespace->TopStack();
    whitespace->PopStack();
    Value* lhs = whitespace->TopStack();
    whitespace->PopStack();

    Value* result = whitespace->GetBuilder()->CreateExactSDiv(lhs, rhs, "IntDivStatement");
    whitespace->PushStack(result);
}

void ModuloStatement::CodeGen(Whitespace* whitespace)
{
    Value* rhs = whitespace->TopStack();
    whitespace->PopStack();
    Value* lhs = whitespace->TopStack();
    whitespace->PopStack();

    Value* result = whitespace->GetBuilder()->CreateSRem(lhs, rhs, "ModuloStatement");
    whitespace->PushStack(result);
}

void HeapStoreStatement::CodeGen(Whitespace* whitespace)
{
    Value* value = whitespace->TopStack();
    whitespace->PopStack();
    Value* address = whitespace->TopStack();
    whitespace->PopStack();

    whitespace->HeapStore(address, value);
}

void HeapRetrieveStatement::CodeGen(Whitespace* whitespace)
{
    Value* address = whitespace->TopStack();
    whitespace->PopStack();

    Value* value = whitespace->HeapRetrieve(address);
    whitespace->PushStack(value);
}

void OutputCharacterStatement::CodeGen(Whitespace* whitespace)
{
    Value* val = whitespace->TopStack();
    whitespace->PopStack();
    whitespace->PutChar(val);
}

void OutputNumberStatement::CodeGen(Whitespace* whitespace)
{
    Value* val = whitespace->TopStack();
    whitespace->PopStack();
    // Convert it to a number character
    Value* number = whitespace->GetBuilder()->CreateAdd(val, whitespace->GetBuilder()->getInt64('0'));
    whitespace->PutChar(number);
}

void ReadCharacterStatement::CodeGen(Whitespace* whitespace)
{
    Value* address = whitespace->TopStack();
    whitespace->PopStack();
    Value* read = whitespace->GetChar();
    whitespace->HeapStore(address, read);
}

void ReadNumberStatement::CodeGen(Whitespace* whitespace)
{
    Value* address = whitespace->TopStack();
    whitespace->PopStack();
    Value* read = whitespace->GetChar();
    whitespace->HeapStore(address, read);
}

void MarkLabelStatement::CodeGen(Whitespace* whitespace)
{
    if (whitespace->ProgramEnded())
    {
         // Create a function instead of a block
        Function* func = cast<Function>(whitespace->GetModule()->getOrInsertFunction(tostring(_label), whitespace->GetBuilder()->getVoidTy(), nullptr));
        BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));
        if (block == nullptr)
        {
            block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "FuncBB", func);
            whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), func);
        }
        whitespace->GetBuilder()->SetInsertPoint(block);
        return;
    }

    // Try to get the block, it might have been created in a jump statement
    BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));

    if (block == nullptr)
    {
        block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "Inner", whitespace->GetMainFunction());
        whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), block);
    }

    whitespace->GetBuilder()->SetInsertPoint(block);
}

void UnconditionalJumpStatement::CodeGen(Whitespace* whitespace)
{
    BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));

    if (block == nullptr)
    {
        block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "Inner", whitespace->GetMainFunction());
        whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), block);
    }

    whitespace->GetBuilder()->CreateBr(block);
}

void StackZeroJumpStatement::CodeGen(Whitespace* whitespace)
{
    Value* top = whitespace->TopStack();
    Value* zeroCheck = whitespace->GetBuilder()->CreateICmpEQ(top, whitespace->GetBuilder()->getInt64(0), "zeroCheck");

    BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));

    if (block == nullptr)
    {
        block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "Inner", whitespace->GetMainFunction());
        whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), block);
    }

    BasicBlock* elseBlock = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "SZJElse", whitespace->GetMainFunction());
    whitespace->GetBuilder()->CreateCondBr(zeroCheck, block, elseBlock);

    whitespace->GetBuilder()->SetInsertPoint(elseBlock);
}

void StackNegativeJumpStatement::CodeGen(Whitespace* whitespace)
{
    Value* top = whitespace->TopStack();
    Value* negCheck = whitespace->GetBuilder()->CreateICmpSLT(top, whitespace->GetBuilder()->getInt64(0), "negCheck");
    BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));

    if (block == nullptr)
    {
        block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "Inner", whitespace->GetMainFunction());
        whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), block);
    }

    BasicBlock* elseBlock = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "SNJElse", whitespace->GetMainFunction());
    whitespace->GetBuilder()->CreateCondBr(negCheck, block, elseBlock);

    whitespace->GetBuilder()->SetInsertPoint(elseBlock);
}

void EndProgramStatement::CodeGen(Whitespace* whitespace)
{
    whitespace->GetBuilder()->CreateBr(whitespace->GetEndBlock());
}

void CallStatement::CodeGen(Whitespace* whitespace)
{
    BasicBlock* block = cast<BasicBlock>(whitespace->GetJumpLabel(whitespace->GetBuilder()->getInt64(_label)));

    if (block == nullptr)
    {
        Function* func = cast<Function>(whitespace->GetModule()->getOrInsertFunction(tostring(_label), whitespace->GetBuilder()->getVoidTy(), nullptr));
        block = BasicBlock::Create(whitespace->GetBuilder()->getContext(), "Inner", func);
        whitespace->SetJumpLabel(whitespace->GetBuilder()->getInt64(_label), block);
    }

    whitespace->GetBuilder()->CreateCall(block->getParent(), "Call");
}

void EndSubStatement::CodeGen(Whitespace* whitespace)
{
    whitespace->GetBuilder()->CreateRet(nullptr);
    whitespace->MarkEndOfProgram();
}
