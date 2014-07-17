#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "Whitespace.h"
#include "catch.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Test the heap manipulation statements", "[statements heap]") {
    std::stringstream str;
    str << "   \t    \n   \t   \t\n\t\t    \t    \n   \t  \t\t\n\t\t    \t    \n\t\t\t   \t   \t\n\t\t\t";
    Lexer lexer(str);
    Parser parser(lexer);

    Whitespace whitespace;

    auto statement = parser.ParseStatement(); // Push 16
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Push 17
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Store
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt64(16)) == whitespace.GetBuilder()->getInt64(17));
    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt64(17)) == nullptr);

    statement = parser.ParseStatement(); // Push 16
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Push 19
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Store
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt64(16)) == whitespace.GetBuilder()->getInt64(19));

    statement = parser.ParseStatement(); // Push 16
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Retrieve
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    REQUIRE(whitespace.StackSize() == 1);
    REQUIRE(whitespace.TopStack() == whitespace.GetBuilder()->getInt64(19));

    whitespace.HeapStore(whitespace.GetBuilder()->getInt64(17), whitespace.GetBuilder()->getInt64(15));

    statement = parser.ParseStatement(); // Push 17
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    statement = parser.ParseStatement(); // Heap Retrieve
    REQUIRE(statement != nullptr);

    statement->CodeGen(&whitespace);

    REQUIRE(whitespace.StackSize() == 2);
    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt64(17)) == whitespace.GetBuilder()->getInt64(15));
}
