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
    virtual std::string ToString() = 0;
};

class PushStatement : public Statement
{
public:
    PushStatement(int64_t number) : _number(number) {}
    ~PushStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }

    std::string ToString() override { return "PushStatement"; }

private:
    int64_t _number;
};

class DuplicateTopStatement : public Statement
{
public:
    ~DuplicateTopStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "DuplicateTopStatement"; }
};

class CopyStatement : public Statement
{
public:
    CopyStatement(int64_t number) : _number(number) {}
    ~CopyStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }

    std::string ToString() override { return "CopyStatement"; }
private:
    int64_t _number;
};

class SwapStatement : public Statement
{
public:
    ~SwapStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "SwapStatement"; }
};

class DiscardTopStatement : public Statement
{
public:
    ~DiscardTopStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "DiscardTopStatement"; }
};

class SlideStatement : public Statement
{
public:
    SlideStatement(int64_t number) : _number(number) {}
    ~SlideStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    int64_t GetNumber() { return _number; }

    std::string ToString() override { return "SlideStatement"; }
private:
    int64_t _number;
};

class AdditionStatement : public Statement
{
public:
    ~AdditionStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "AdditionStatement"; }
};

class SubstractionStatement : public Statement
{
public:
    ~SubstractionStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "SubstractionStatement"; }
};

class MultiplicationStatement : public Statement
{
public:
    ~MultiplicationStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "MultiplicationStatement"; }
};

class IntegerDivisionStatement : public Statement
{
public:
    ~IntegerDivisionStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "IntegerDivisionStatement"; }
};

class ModuloStatement : public Statement
{
public:
    ~ModuloStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "ModuloStatement"; }
};

class HeapStoreStatement : public Statement
{
public:
    ~HeapStoreStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "HeapStoreStatement"; }
};

class HeapRetrieveStatement : public Statement
{
public:
    ~HeapRetrieveStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "HeapRetrieveStatement"; }
};

class MarkLabelStatement : public Statement
{
public:
    MarkLabelStatement(uint64_t label) : _label(label) {}
    ~MarkLabelStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "MarkLabelStatement"; }

private:
    uint64_t _label; // We use a number instead of a string for the label
};

class CallStatement : public Statement
{
public:
    CallStatement(uint64_t label) : _label(label) {}
    ~CallStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "CallStatement"; }
private:
    uint64_t _label;
};

class UnconditionalJumpStatement : public Statement
{
public:
    UnconditionalJumpStatement(uint64_t label) : _label(label) {}
    ~UnconditionalJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "UnconditionalJumpStatement"; }

private:
    uint64_t _label;
};

class StackZeroJumpStatement : public Statement
{
public:
    StackZeroJumpStatement(uint64_t label) : _label(label) {}
    ~StackZeroJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "StackZeroJumpStatement"; }

private:
    uint64_t _label;
};

class StackNegativeJumpStatement : public Statement
{
public:
    StackNegativeJumpStatement(uint64_t label) : _label(label) {}
    ~StackNegativeJumpStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "StackNegativeJumpStatement"; }
private:
    uint64_t _label;
};

class EndSubStatement : public Statement
{
public:
    ~EndSubStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "EndSubStatement"; }
};

class EndProgramStatement : public Statement
{
public:
    ~EndProgramStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "EndProgramStatement"; }
};

class OutputCharacterStatement : public Statement
{
public:
    ~OutputCharacterStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "OutputCharacterStatement"; }
};

class OutputNumberStatement : public Statement
{
public:
    ~OutputNumberStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "OutputNumberStatement"; }
};

class ReadCharacterStatement : public Statement
{
public:
    ~ReadCharacterStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "ReadCharacterStatement"; }
};

class ReadNumberStatement : public Statement
{
public:
    ~ReadNumberStatement() {}

    void CodeGen(Whitespace* whitespace) override;

    std::string ToString() override { return "ReadNumberStatement"; }
};

#endif
