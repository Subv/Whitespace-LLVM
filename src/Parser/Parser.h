#ifndef PARSER_H
#define PARSER_H

#include <cstdint>

class Statement;
class Lexer;

class Parser
{
public:
    Parser(Lexer& lexer);
    ~Parser();

    Statement* ParseStatement();
    Statement* ParseStackManipulationStatement();
    Statement* ParseArithmeticStatement();
    Statement* ParseHeapAccessStatement();
    Statement* ParseFlowControlStatement();
    Statement* ParseIOStatement();

    int64_t ParseNumber();
private:
    Lexer& _lexer;
};

#endif
