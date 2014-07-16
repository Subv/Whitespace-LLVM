#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "catch.hpp"
#include <sstream>
#include <memory>

TEST_CASE("Test the parsing of the stack push statement", "[parser stack push]") {
    std::stringstream str;
    str << "   \t\n  \t\t\n   \t \t \n  \t\t \t \n   \n  \t\n";
    Lexer lexer(str);
    Parser parser(lexer);

    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == 1);
    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == -1);
    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == 10);
    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == -10);
    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == 0);
    REQUIRE(std::static_pointer_cast<PushStatement>(parser.ParseStatement())->GetNumber() == 0);
    REQUIRE(parser.ParseStatement() == nullptr);
}

TEST_CASE("Test the parsing of the stack copy statement", "[parser stack copy]") {
    std::stringstream str;
    str << " \t  \t\t\n \t  \t\t    \n \t \t   \t \t\n";
    Lexer lexer(str);
    Parser parser(lexer);

    REQUIRE(std::static_pointer_cast<CopyStatement>(parser.ParseStatement())->GetNumber() == 3);
    REQUIRE(std::static_pointer_cast<CopyStatement>(parser.ParseStatement())->GetNumber() == 48);
    REQUIRE(std::static_pointer_cast<CopyStatement>(parser.ParseStatement())->GetNumber() == -5);
    REQUIRE(parser.ParseStatement() == nullptr);
}

TEST_CASE("Test the parsing of the stack slide statement", "[parser stack slide]") {
    std::stringstream str;
    str << " \t\n \t\t\n \t\n \t\t    \n \t\n\t   \t \t\t\n";
    Lexer lexer(str);
    Parser parser(lexer);

    REQUIRE(std::static_pointer_cast<SlideStatement>(parser.ParseStatement())->GetNumber() == 3);
    REQUIRE(std::static_pointer_cast<SlideStatement>(parser.ParseStatement())->GetNumber() == 48);
    REQUIRE(std::static_pointer_cast<SlideStatement>(parser.ParseStatement())->GetNumber() == -11);
    REQUIRE(parser.ParseStatement() == nullptr);
}
