#include "Whitespace.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

#include <iostream>
using namespace llvm;

Whitespace::Whitespace()
{
    _module = new Module("MainModule", _context);

    // Setup a start function
    _mainFunction = cast<Function>(_module->getOrInsertFunction("whitespace", Type::getVoidTy(_context), nullptr));

    auto startBlock = BasicBlock::Create(_context, "StartBlock", _mainFunction);

    _builder = new IRBuilder<>(startBlock);

    auto end = BasicBlock::Create(_context, "whitespaceReturn", _mainFunction);
    ReturnInst::Create(_context, end);

    // Insert the branch at the end
    _builder->SetInsertPoint(_builder->CreateBr(end));

    // Create references to getchar and putchar
    _putchar = cast<Function>(_module->getOrInsertFunction("putchar", _builder->getInt32Ty(), _builder->getInt32Ty(), nullptr));
    _getchar = cast<Function>(_module->getOrInsertFunction("getchar", _builder->getInt32Ty(), nullptr));
}

Whitespace::~Whitespace()
{
    delete _builder;
    delete _module;
}

void Whitespace::PutChar(Value* val)
{
    auto call = _builder->CreateCall(_putchar, val, "call putchar");
    call->setTailCall(false);
}

void Whitespace::Dump()
{
    _module->dump();
}
