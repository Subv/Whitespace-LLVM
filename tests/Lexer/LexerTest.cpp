#include "Lexer.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("Test data is lexed", "[lexer]") {
    std::stringstream str;
    str << "   \tfd \n f\n";
    Lexer lexer(str);
    REQUIRE(lexer.GetToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_TAB);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_NONE);
    REQUIRE(lexer.GetToken() == Lexer::TOKEN_NONE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_NONE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_LF);
    REQUIRE(lexer.GetToken() == Lexer::TOKEN_LF);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_SPACE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_NONE);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_LF);
    REQUIRE(lexer.GetToken() == Lexer::TOKEN_LF);
    REQUIRE(lexer.GetNextToken() == Lexer::TOKEN_NONE); // The lexer should return TOKEN_NONE when EOF is hit
}
