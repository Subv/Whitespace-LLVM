#include <fstream>
#include <iostream>
#include "Lexer.h"

int main(int argc, char *argv[])
{
    std::ifstream file;
    file.open("test.ws", std::ifstream::in);

    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return 0;
    }

    Lexer lexer(file);

    while (!lexer.Finished())
    {
        switch (lexer.GetToken())
        {
            case Lexer::TOKEN_LF:
                std::cout << "Line Feed" << std::endl;
                break;
            case Lexer::TOKEN_SPACE:
                std::cout << "Space" << std::endl;
                break;
            case Lexer::TOKEN_TAB:
                std::cout << "Tab" << std::endl;
                break;
            case Lexer::TOKEN_NONE:
                std::cout << "Ignored" << std::endl;
                break;
        }

        lexer.GetNextToken();
    }

    std::cin.get();

    return 0;
}
