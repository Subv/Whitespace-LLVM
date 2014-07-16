#ifndef LEXER_H
#define LEXER_H

#include <istream>

class Lexer
{
public:
    enum Tokens
    {
        TOKEN_NONE,
        TOKEN_LF, // Line Feed
        TOKEN_SPACE,
        TOKEN_TAB
    };

    Lexer(std::istream& stream);
    ~Lexer();

    Tokens GetToken() { return _currentToken; }
    Tokens GetNextToken();
    Tokens Peek();

    bool Finished() { return _stream.eof(); }
private:
    Tokens ParseToken(char input);
    Tokens _currentToken;
    std::istream& _stream;
};

#endif
