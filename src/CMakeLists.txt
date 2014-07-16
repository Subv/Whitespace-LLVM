file(GLOB_RECURSE Sources *.cpp *.h)

if (NOT BUILD_TESTS)
    add_executable(Whitespace-LLVM ${Sources})
    install(TARGETS Whitespace-LLVM DESTINATION bin)
else()
    add_library(Whitespace-LLVM ${Sources})
endif()
