file(GLOB_RECURSE Sources *.h *.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/src)
    
link_libraries(Whitespace-LLVM)
add_executable(Tests ${Sources})
