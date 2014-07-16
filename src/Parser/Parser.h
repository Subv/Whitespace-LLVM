#ifndef PARSER_H
#define PARSER_H

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

    int ParseNumber();
private:
    Lexer& _lexer;
};

#endif
