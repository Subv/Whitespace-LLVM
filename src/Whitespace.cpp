#include "Whitespace.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/Analysis/Verifier.h"

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

    // Create references to getchar and putchar
    _putchar = cast<Function>(_module->getOrInsertFunction("putchar", _builder->getInt32Ty(), _builder->getInt32Ty(), nullptr));
    _getchar = cast<Function>(_module->getOrInsertFunction("getchar", _builder->getInt32Ty(), nullptr));

    _runtimeStack = _builder->CreateAlloca(_builder->getInt64Ty(), _builder->getInt64(65335), "ProgramStack");
    _stackIndex = _builder->CreateAlloca(_builder->getInt32Ty(), nullptr, "StackPointer");
    _builder->CreateStore(_builder->getInt32(-1), _stackIndex);
}

Whitespace::~Whitespace()
{
    delete _builder;
}

void Whitespace::PopStack()
{
    _builder->CreateStore(_builder->CreateSub(_builder->CreateLoad(_stackIndex), _builder->getInt32(1)), _stackIndex);
}

Value* Whitespace::TopStack()
{
    Value* address = _builder->CreateGEP(_runtimeStack, _builder->CreateLoad(_stackIndex));
    return _builder->CreateLoad(address);
}

void Whitespace::PushStack(Value* val)
{
    _builder->CreateStore(_builder->CreateAdd(_builder->CreateLoad(_stackIndex), _builder->getInt32(1)), _stackIndex);
    Value* address = _builder->CreateGEP(_runtimeStack, _builder->CreateLoad(_stackIndex));
    _builder->CreateStore(val, address);
}

Value* Whitespace::StackSize()
{
    return _builder->CreateAdd(_builder->CreateLoad(_stackIndex), _builder->getInt32(1));
}

void Whitespace::HeapStore(Value* key, Value* value)
{
    // TODO
}

Value* Whitespace::HeapRetrieve(Value* key)
{
    // TODO
    return nullptr;
}

void Whitespace::PutChar(Value* val)
{
    auto trunc = _builder->CreateTrunc(val, _builder->getInt32Ty());
    auto call = _builder->CreateCall(_putchar, trunc, "_putchar");
    call->setTailCall(false);
}

Value* Whitespace::GetChar()
{
    auto call = _builder->CreateCall(_getchar, "_getchar");
    call->setTailCall(false);
    return _builder->CreateSExt(call, _builder->getInt64Ty());
}

void Whitespace::Dump()
{
    _module->dump();
}

GenericValue Whitespace::Run()
{
    verifyModule(*_module);

    InitializeNativeTarget();
    ExecutionEngine* ee = EngineBuilder(_module).create();
    Function* func = GetMainFunction();
    std::vector<GenericValue> args;
    GenericValue gv = ee->runFunction(func, args);

    delete ee;
    return gv;
}
