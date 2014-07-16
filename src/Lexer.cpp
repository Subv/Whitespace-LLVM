#include "Lexer.h"

Lexer::Lexer(std::istream& stream) : _stream(stream), _currentToken(TOKEN_NONE)
{
    // Read the first token in the file
    GetNextToken();
}

Lexer::~Lexer()
{

}

Lexer::Tokens Lexer::GetNextToken()
{
    _currentToken = ParseToken(_stream.get());
    return GetToken();
}

Lexer::Tokens Lexer::Peek()
{
    return ParseToken(_stream.peek());
}

Lexer::Tokens Lexer::ParseToken(char input)
{
    if (_stream.eof())
        return TOKEN_NONE;

    switch (input)
    {
        case ' ':
            return TOKEN_SPACE;
            break;
        case '\t':
            return TOKEN_TAB;
            break;
        case '\n':
            return TOKEN_LF;
            break;
        default:
            break;
    }

    return TOKEN_NONE;
}
