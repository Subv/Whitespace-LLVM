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

private:
    int64_t _number;
};

#endif
