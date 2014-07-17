#ifndef WHITESPACE_H
#define WHITESPACE_H

#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include <unordered_map>

class Whitespace
{
public:
    Whitespace();
    ~Whitespace();

    void PopStack();
    llvm::Value* TopStack();
    void PushStack(llvm::Value* val);
    llvm::Value* StackSize() { return _stackIndex; }

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

    void MarkEndOfProgram() { _programEnded = true; }
    bool ProgramEnded() { return _programEnded; }

    void Dump();
private:
    llvm::LLVMContext _context;
    llvm::Module* _module;
    llvm::IRBuilder<>* _builder;
    llvm::Function* _mainFunction;
    llvm::BasicBlock* _endBlock;
    llvm::Function* _putchar;
    llvm::Function* _getchar;
    llvm::Value* _runtimeStack;
    llvm::Value* _stackIndex; // Current stack index
    bool _programEnded;
    std::unordered_map<llvm::Value*, llvm::Value*> _heap;
    std::unordered_map<llvm::Value*, llvm::Value*> _labels;
};

#endif
