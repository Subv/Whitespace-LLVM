#include "Lexer.h"

Lexer::Lexer(std::istream& stream) : _currentToken(TOKEN_NONE), _stream(stream)
{

}

Lexer::~Lexer()
{

}

Lexer::Tokens Lexer::GetNextToken()
{
    // Ignore all other characters unless we reach the end of the file
    do
        _currentToken = ParseToken(_stream.get());
    while (_currentToken == TOKEN_NONE && !_stream.eof());

    if (_stream.eof())
        return TOKEN_NONE;

    return GetToken();
}

Lexer::Tokens Lexer::ParseToken(char input)
{
    if (_stream.eof())
        return TOKEN_NONE;

    switch (input)
    {
        case ' ':
            return TOKEN_SPACE;
        case '\t':
            return TOKEN_TAB;
        case '\n':
            return TOKEN_LF;
        default:
            break;
    }

    return TOKEN_NONE;
}
