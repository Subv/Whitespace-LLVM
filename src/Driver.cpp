#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Statements.h"
#include "Whitespace.h"

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Analysis/Verifier.h"

#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

using namespace llvm;

int main(int argc, char *argv[])
{
    std::ifstream file;
    file.open("test.ws", std::ifstream::in);

    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return 0;
    }

    std::stringstream str;
    str << "   \t     \t\n\t\n \t"; // Pushes 0x41 to the stack, and then prints it

    Lexer lexer(file);
    Parser parser(lexer);

    Whitespace* whitespace = new Whitespace();

    std::shared_ptr<Statement> statement = parser.ParseStatement();

    // Now generate the code
    while (statement != nullptr)
    {
        statement->CodeGen(whitespace);
        std::cout << statement->ToString() << std::endl;

        statement = parser.ParseStatement();
    }

    //whitespace->Dump();

    InitializeNativeTarget();
    ExecutionEngine* ee = EngineBuilder(whitespace->GetModule()).create();
    Function* func = whitespace->GetMainFunction();
    std::vector<GenericValue> args;
    ee->runFunction(func, args);

    delete ee;
    delete whitespace;

    llvm_shutdown();
    file.close();
    return 0;
}
