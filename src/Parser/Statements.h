#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <cstdint>

class Statement
{
public:
    Statement() {}
    virtual ~Statement() {}
};

class PushStatement : public Statement
{
public:
    PushStatement(int64_t number) : _number(number) {}
    ~PushStatement() {}

    int64_t GetNumber() { return _number; }

private:
    int64_t _number;
};

class DuplicateTopStatement : public Statement
{
public:
    ~DuplicateTopStatement() {}
};

class CopyStatement : public Statement
{
public:
    CopyStatement(int64_t number) : _number(number) {}
    ~CopyStatement() {}

    int64_t GetNumber() { return _number; }
private:
    int64_t _number;
};

class SwapStatement : public Statement
{
public:
    ~SwapStatement() {}
};

class DiscardTopStatement : public Statement
{
public:
    ~DiscardTopStatement() {}
};

class SlideStatement : public Statement
{
public:
    SlideStatement(int64_t number) : _number(number) {}
    ~SlideStatement() {}

    int64_t GetNumber() { return _number; }
private:
    int64_t _number;
};

class AdditionStatement : public Statement
{
public:
    ~AdditionStatement() {}
};

class SubstractionStatement : public Statement
{
public:
    ~SubstractionStatement() {}
};

class MultiplicationStatement : public Statement
{
public:
    ~MultiplicationStatement() {}
};

class IntegerDivisionStatement : public Statement
{
public:
    ~IntegerDivisionStatement() {}
};

class ModuloStatement : public Statement
{
public:
    ~ModuloStatement() {}
};

class HeapStoreStatement : public Statement
{
public:
    ~HeapStoreStatement() {}
};

class HeapRetrieveStatement : public Statement
{
public:
    ~HeapRetrieveStatement() {}
};

class MarkLabelStatement : public Statement
{
public:
    MarkLabelStatement(uint64_t label) : _label(label) {}
    ~MarkLabelStatement() {}

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

private:
    uint64_t _label;
};

class StackZeroJumpStatement : public Statement
{
public:
    StackZeroJumpStatement(uint64_t label) : _label(label) {}
    ~StackZeroJumpStatement() {}

private:
    uint64_t _label;
};

class StackNegativeJumpStatement : public Statement
{
public:
    StackNegativeJumpStatement(uint64_t label) : _label(label) {}
    ~StackNegativeJumpStatement() {}

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
};

class OutputCharacterStatement : public Statement
{
public:
    ~OutputCharacterStatement() {}
};

class OutputNumberStatement : public Statement
{
public:
    ~OutputNumberStatement() {}
};

class ReadCharacterStatement : public Statement
{
public:
    ~ReadCharacterStatement() {}
};

class ReadNumberStatement : public Statement
{
public:
    ~ReadNumberStatement() {}
};

#endif
