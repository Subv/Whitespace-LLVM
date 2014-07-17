#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "llvm/IR/IRBuilder.h"
#include <cstdint>
#include <stack>

class Whitespace;

class Statement
{
public:
    Statement() {}
    virtual ~Statement() {}
    virtual void CodeGen(Whitespace* whitespace) {}
};

class PushStatement : public Statement
{
public:
    PushStatement(int64_t number) : _number(number) {}
    ~PushStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }

private:
    int64_t _number;
};

class DuplicateTopStatement : public Statement
{
public:
    ~DuplicateTopStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class CopyStatement : public Statement
{
public:
    CopyStatement(int64_t number) : _number(number) {}
    ~CopyStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }
private:
    int64_t _number;
};

class SwapStatement : public Statement
{
public:
    ~SwapStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class DiscardTopStatement : public Statement
{
public:
    ~DiscardTopStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class SlideStatement : public Statement
{
public:
    SlideStatement(int64_t number) : _number(number) {}
    ~SlideStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }
private:
    int64_t _number;
};

class AdditionStatement : public Statement
{
public:
    ~AdditionStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class SubstractionStatement : public Statement
{
public:
    ~SubstractionStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class MultiplicationStatement : public Statement
{
public:
    ~MultiplicationStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class IntegerDivisionStatement : public Statement
{
public:
    ~IntegerDivisionStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class ModuloStatement : public Statement
{
public:
    ~ModuloStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class HeapStoreStatement : public Statement
{
public:
    ~HeapStoreStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class HeapRetrieveStatement : public Statement
{
public:
    ~HeapRetrieveStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class MarkLabelStatement : public Statement
{
public:
    MarkLabelStatement(uint64_t label) : _label(label) {}
    ~MarkLabelStatement() {}

    void CodeGen(Whitespace* whitespace) override;

private:
    uint64_t _label; // We use a number instead of a string for the label
};

class CallStatement : public Statement
{
public:
    CallStatement(uint64_t label) : _label(label) {}
    ~CallStatement() {}

private:
    uint64_t _label;
};

class UnconditionalJumpStatement : public Statement
{
public:
    UnconditionalJumpStatement(uint64_t label) : _label(label) {}
    ~UnconditionalJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

private:
    uint64_t _label;
};

class StackZeroJumpStatement : public Statement
{
public:
    StackZeroJumpStatement(uint64_t label) : _label(label) {}
    ~StackZeroJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

private:
    uint64_t _label;
};

class StackNegativeJumpStatement : public Statement
{
public:
    StackNegativeJumpStatement(uint64_t label) : _label(label) {}
    ~StackNegativeJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

private:
    uint64_t _label;
};

class EndSubStatement : public Statement
{
public:
    ~EndSubStatement() {}
};

class EndProgramStatement : public Statement
{
public:
    ~EndProgramStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class OutputCharacterStatement : public Statement
{
public:
    ~OutputCharacterStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class OutputNumberStatement : public Statement
{
public:
    ~OutputNumberStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class ReadCharacterStatement : public Statement
{
public:
    ~ReadCharacterStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

class ReadNumberStatement : public Statement
{
public:
    ~ReadNumberStatement() {}

    void CodeGen(Whitespace* whitespace) override;
};

#endif
