project(Whitespace-LLVM)
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_BUILD_TYPE "Debug")

# A convenience variable:
find_package(LLVM REQUIRED COMPONENTS jit native interpreter)

add_definitions(${LLVM_CPP_FLAGS})
link_libraries(${LLVM_LIBRARIES} ${LLVM_LD_FLAGS})
link_directories(${LLVM_LIBRARY_DIRS})
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(src)


