#ifndef WHITESPACE_H
#define WHITESPACE_H

#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include <stack>
#include <unordered_map>

class Whitespace
{
public:
    Whitespace();
    ~Whitespace();

    void PopStack() { _stack.pop(); }
    llvm::Value* TopStack() { return _stack.top(); }
    void PushStack(llvm::Value* val) { _stack.push(val); }
    size_t StackSize() { return _stack.size(); }

    void HeapStore(llvm::Value* key, llvm::Value* value) { _heap[key] = value; }
    llvm::Value* HeapRetrieve(llvm::Value* key) { return _heap[key]; }

    llvm::IRBuilder<>* GetBuilder() { return _builder; }
    llvm::Module* GetModule() { return _module; }

    void PutChar(llvm::Value* val);
    llvm::Value* GetChar();

    llvm::Value* GetJumpLabel(llvm::Value* key) { return _labels[key]; }
    void SetJumpLabel(llvm::Value* key, llvm::Value* func) { _labels[key] = func; }

    llvm::Function* GetMainFunction() { return _mainFunction; }
    llvm::BasicBlock* GetEndBlock() { return _endBlock; }

    void Dump();
private:
    std::stack<llvm::Value*> _stack;
    llvm::LLVMContext _context;
    llvm::Module* _module;
    llvm::IRBuilder<>* _builder;
    llvm::Function* _mainFunction;
    llvm::BasicBlock* _endBlock;
    llvm::Function* _putchar;
    llvm::Function* _getchar;
    std::unordered_map<llvm::Value*, llvm::Value*> _heap;
    std::unordered_map<llvm::Value*, llvm::Value*> _labels;
};

#endif
