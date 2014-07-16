#ifndef STATEMENTS_H
#define STATEMENTS_H

class Statement
{
public:
    Statement() {}
    virtual ~Statement() {}
};

class PushStatement : public Statement
{
public:
    PushStatement(int number) : _number(number) {}
    ~PushStatement() {}

    int GetNumber() { return _number; }

private:
    int _number;
};

class DuplicateTopStatement : public Statement
{
public:
    ~DuplicateTopStatement() {}
};

class CopyStatement : public Statement
{
public:
    CopyStatement(int number) : _number(number) {}
    ~CopyStatement() {}

private:
    int _number;
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
    SlideStatement(int number) : _number(number) {}
    ~SlideStatement() {}

private:
    int _number;
};

#endif
