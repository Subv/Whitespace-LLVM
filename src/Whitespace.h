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

    void Dump();
private:
    std::stack<llvm::Value*> _stack;
    llvm::LLVMContext _context;
    llvm::Module* _module;
    llvm::IRBuilder<>* _builder;
    llvm::Function* _mainFunction;
    llvm::Function* _putchar;
    llvm::Function* _getchar;
    std::unordered_map<llvm::Value*, llvm::Value*> _heap;
};

#endif
