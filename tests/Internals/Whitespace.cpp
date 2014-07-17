#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "Whitespace.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("Test the whitespace class general behavior", "[whitespace]") {
    Whitespace whitespace;

    REQUIRE(whitespace.GetBuilder() != nullptr);
    REQUIRE(whitespace.GetModule() != nullptr);
}

TEST_CASE("Test the whitespace class stack implementation", "[whitespace stack]") {
    Whitespace whitespace;

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(0));

    whitespace.PushStack(whitespace.GetBuilder()->getInt64(15));

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(1));

    whitespace.PushStack(whitespace.GetBuilder()->getInt64(16));

    REQUIRE(whitespace.TopStack() != nullptr);

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(2));

    whitespace.PopStack();

    // Make the function return the top value in its stack
    whitespace.GetBuilder()->CreateRet(whitespace.TopStack());

    auto ret = whitespace.Run();

    REQUIRE(ret.IntVal == 15);

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(1));

    whitespace.PopStack();

    REQUIRE(whitespace.StackSize() == whitespace.GetBuilder()->getInt32(0));
}

TEST_CASE("Test the whitespace class heap implementation", "[whitespace heap]") {
    Whitespace whitespace;

    REQUIRE(whitespace.HeapRetrieve(nullptr) == nullptr);
    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt32(64)) == nullptr);

    whitespace.HeapStore(whitespace.GetBuilder()->getInt32(64), whitespace.GetBuilder()->getInt8(15));

    whitespace.GetBuilder()->CreateRet(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt32(64)));

    auto ret = whitespace.Run();

    REQUIRE(ret.IntVal == 15);

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt8(64)) == nullptr);
}
