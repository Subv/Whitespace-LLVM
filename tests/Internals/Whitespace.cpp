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

    REQUIRE(whitespace.StackSize() == 0);

    whitespace.PushStack(nullptr);

    REQUIRE(whitespace.StackSize() == 1);

    REQUIRE(whitespace.TopStack() == nullptr);

    whitespace.PushStack(whitespace.GetBuilder()->getInt32(16));

    REQUIRE(whitespace.TopStack() != nullptr);

    llvm::Value* val = whitespace.TopStack();

    REQUIRE(whitespace.StackSize() == 2);

    // Constants share the same instance
    REQUIRE(val == whitespace.GetBuilder()->getInt32(16));

    whitespace.PopStack();

    REQUIRE(whitespace.StackSize() == 1);
    REQUIRE(whitespace.TopStack() == nullptr);

    whitespace.PopStack();

    REQUIRE(whitespace.StackSize() == 0);
}

TEST_CASE("Test the whitespace class heap implementation", "[whitespace heap]") {
    Whitespace whitespace;

    REQUIRE(whitespace.HeapRetrieve(nullptr) == nullptr);
    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt32(64)) == nullptr);

    whitespace.HeapStore(whitespace.GetBuilder()->getInt32(64), whitespace.GetBuilder()->getInt8(15));

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt32(64)) == whitespace.GetBuilder()->getInt8(15));
    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt8(64)) == nullptr);

    whitespace.HeapStore(whitespace.GetBuilder()->getInt32(64), nullptr);

    REQUIRE(whitespace.HeapRetrieve(whitespace.GetBuilder()->getInt32(64)) == nullptr);
}
