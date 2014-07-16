#include "Parser.h"
#include "Statements.h"
#include "Lexer/Lexer.h"
#include <iostream>

Parser::Parser(Lexer &lexer) : _lexer(lexer)
{

}

Parser::~Parser()
{

}

Statement *Parser::ParseStatement()
{
    // Lexer::GetNextToken reads the next token and updates the Lexer
    if (_lexer.GetNextToken() == Lexer::TOKEN_NONE)
        return nullptr;

    switch (_lexer.GetToken())
    {
        case Lexer::TOKEN_SPACE:
            return ParseStackManipulationStatement();
        case Lexer::TOKEN_LF:
            return ParseFlowControlStatement();
        case Lexer::TOKEN_TAB:
        {
            switch (_lexer.GetNextToken())
            {
                case Lexer::TOKEN_SPACE:
                    return ParseArithmeticStatement();
                case Lexer::TOKEN_TAB:
                    return ParseHeapAccessStatement();
                case Lexer::TOKEN_LF:
                    return ParseIOStatement();
                default:
                    return nullptr;
            }
        }
        default:
            break;
    }

    return nullptr;
}

Statement *Parser::ParseStackManipulationStatement()
{
    if (_lexer.GetNextToken() == Lexer::TOKEN_NONE)
        return nullptr;

    switch (_lexer.GetToken())
    {
        case Lexer::TOKEN_SPACE:
            return new PushStatement(ParseNumber());
    }

    return nullptr;
}

Statement *Parser::ParseArithmeticStatement()
{
    return nullptr;
}

Statement *Parser::ParseHeapAccessStatement()
{
    return nullptr;
}

Statement *Parser::ParseFlowControlStatement()
{
    return nullptr;
}

Statement *Parser::ParseIOStatement()
{
    return nullptr;
}

// Reads from the Lexer in binary format until [LF] is reached and converts the value from binary to decimal
// [Space] = 0 [Tab] = 1
int Parser::ParseNumber()
{
    int number = 0;
    // The first value represents the sign of the number
    Lexer::Tokens sign = _lexer.GetNextToken();

    if (sign == Lexer::TOKEN_LF || sign == Lexer::TOKEN_NONE)
        return number;

    Lexer::Tokens bit = _lexer.GetNextToken();
    while (!_lexer.Finished() && bit != Lexer::TOKEN_LF)
    {
        // Shift all the bits to the left and then append the one we just read
        number = number << 1 | (bit == Lexer::TOKEN_SPACE ? 0 : 1);
        bit = _lexer.GetNextToken();
    }

    // Apply the sign
    return number * (sign == Lexer::TOKEN_TAB ? -1 : 1);
}
