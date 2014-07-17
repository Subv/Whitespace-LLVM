#include "Statements.h"
#include "Whitespace.h"

#include "llvm/IR/IRBuilder.h"

#include <iostream>

using namespace llvm;

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
    // TODO: This code is ugly and probably wrong, is there any other way to do this?
    if (whitespace->StackSize() <= _number)
        return;

    std::stack<Value*> backup;

    int n = 0;
    while (n < _number)
    {
        Value* val = whitespace->TopStack();
        backup.push(val);

        whitespace->PopStack();
        ++n;
    }

    Value* duplicate = whitespace->TopStack();

    // Reinsert everything
    while (!backup.empty())
    {
        Value* val = backup.top();
        whitespace->PushStack(val);
    }

    // Now insert the new item
    whitespace->PushStack(duplicate);
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
    std::cout << "Adding" << std::endl;

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

}

void OutputNumberStatement::CodeGen(Whitespace* whitespace)
{
    Value* val = whitespace->TopStack();
    whitespace->PopStack();
    whitespace->PutChar(val);
}

void ReadCharacterStatement::CodeGen(Whitespace* whitespace)
{

}

void ReadNumberStatement::CodeGen(Whitespace* whitespace)
{

}
