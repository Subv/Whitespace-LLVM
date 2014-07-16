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
#endif
