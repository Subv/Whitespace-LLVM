file(GLOB_RECURSE Sources *.cpp *.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT BUILD_TESTS)
    add_executable(Whitespace-LLVM ${Sources})
    install(TARGETS Whitespace-LLVM DESTINATION bin)
else()
    add_library(Whitespace-LLVM ${Sources})
endif()
