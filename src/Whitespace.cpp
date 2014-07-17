#include "Whitespace.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

using namespace llvm;

Whitespace::Whitespace() : _programEnded(false)
{
    _module = new Module("MainModule", _context);

    // Setup a start function
    _mainFunction = cast<Function>(_module->getOrInsertFunction("whitespace", Type::getVoidTy(_context), nullptr));

    auto startBlock = BasicBlock::Create(_context, "StartBlock", _mainFunction);

    _builder = new IRBuilder<>(startBlock);

    _endBlock = BasicBlock::Create(_context, "whitespaceReturn", _mainFunction);
    ReturnInst::Create(_context, _endBlock);

    // Insert the branch at the end
    _builder->SetInsertPoint(_builder->CreateBr(_endBlock));

    // Create references to getchar and putchar
    _putchar = cast<Function>(_module->getOrInsertFunction("putchar", _builder->getInt32Ty(), _builder->getInt32Ty(), nullptr));
    _getchar = cast<Function>(_module->getOrInsertFunction("getchar", _builder->getInt32Ty(), nullptr));

    _runtimeStack = _builder->CreateAlloca(_builder->getInt64Ty(), _builder->getInt64(65335), "ProgramStack");
    _stackIndex = _builder->getInt32(-1);
}

Whitespace::~Whitespace()
{
    delete _builder;
}

void Whitespace::PopStack()
{
    _stackIndex = _builder->CreateSub(_stackIndex, _builder->getInt32(1));
}

Value* Whitespace::TopStack()
{
    Value* address = _builder->CreateGEP(_runtimeStack, _stackIndex);
    return _builder->CreateLoad(address);
}

void Whitespace::PushStack(Value* val)
{
    _stackIndex = _builder->CreateAdd(_stackIndex, _builder->getInt32(1));
    Value* address = _builder->CreateGEP(_runtimeStack, _stackIndex);
    _builder->CreateStore(val, address);
}

void Whitespace::PutChar(Value* val)
{
    auto call = _builder->CreateCall(_putchar, val, "_putchar");
    call->setTailCall(false);
}

Value* Whitespace::GetChar()
{
    auto call = _builder->CreateCall(_getchar, "_getchar");
    call->setTailCall(false);
    return call;
}

void Whitespace::Dump()
{
    _module->dump();
}
