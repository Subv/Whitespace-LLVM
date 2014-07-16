#include <fstream>
#include <iostream>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

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
    Parser parser(lexer);

    parser.ParseStatement();

    file.close();
    return 0;
}
