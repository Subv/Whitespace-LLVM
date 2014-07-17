#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "Whitespace.h"
#include "catch.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Test the heap manipulation statements", "[statements heap]") {
    std::stringstream str;
    str << "   \t    \n   \t  \t\t\n\t\t    \t    \n\t\t\t   \t   \t\n\t\t\t";
    Lexer lexer(str);
    Parser parser(lexer);

    Whitespace whitespace;

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt64(17)) == nullptr);

    auto statement = parser.ParseStatement(); // Push 16
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Push 19
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Store
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Push 16
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Retrieve
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(1));

    whitespace.GetBuilder()->CreateRet(whitespace.TopStack());
    auto ret = whitespace.Run();

    REQUIRE(ret.IntVal == 19);
}
