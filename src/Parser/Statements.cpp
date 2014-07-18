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

    // TODO
}

void HeapRetrieveStatement::CodeGen(Whitespace* whitespace)
{
    Value* address = whitespace->TopStack();
    whitespace->PopStack();

    // TODO
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
    // TODO
}

void UnconditionalJumpStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}

void StackZeroJumpStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}

void StackNegativeJumpStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}

void EndProgramStatement::CodeGen(Whitespace* whitespace)
{
    whitespace->GetBuilder()->CreateBr(whitespace->GetEndBlock());
}

void CallStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}

void EndSubStatement::CodeGen(Whitespace* whitespace)
{
    // TODO
}
