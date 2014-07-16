#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <memory>

class Statement;
class Lexer;

class Parser
{
public:
    Parser(Lexer& lexer);
    ~Parser();

    std::shared_ptr<Statement> ParseStatement();
    std::shared_ptr<Statement> ParseStackManipulationStatement();
    std::shared_ptr<Statement> ParseArithmeticStatement();
    std::shared_ptr<Statement> ParseHeapAccessStatement();
    std::shared_ptr<Statement> ParseFlowControlStatement();
    std::shared_ptr<Statement> ParseIOStatement();

    int64_t ParseNumber();
private:
    Lexer& _lexer;
};

#endif
