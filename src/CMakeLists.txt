file(GLOB_RECURSE Sources *.cpp *.h)

add_executable(Whitespace-LLVM ${Sources})

install(TARGETS Whitespace-LLVM DESTINATION bin)
