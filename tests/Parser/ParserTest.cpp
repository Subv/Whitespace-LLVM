#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("Test the parsing of the stack push statement", "[parser stack push]") {
    std::stringstream str;
    str << "   \t\n  \t\t\n   \t \t \n  \t\t \t \n   \n  \t\n";
    Lexer lexer(str);
    Parser parser(lexer);

    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == 1);
    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == -1);
    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == 10);
    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == -10);
    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == 0);
    REQUIRE(static_cast<PushStatement*>(parser.ParseStatement())->GetNumber() == 0);
}
