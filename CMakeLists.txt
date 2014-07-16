project(Whitespace-LLVM)
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_BUILD_TYPE "Debug")

if (CMAKE_C_COMPILER MATCHES "clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
endif()

# A convenience variable:
find_package(LLVM REQUIRED COMPONENTS jit native interpreter)

add_definitions(${LLVM_CPP_FLAGS})
link_libraries(${LLVM_LIBRARIES} ${LLVM_LD_FLAGS})
link_directories(${LLVM_LIBRARY_DIRS})
include_directories(${LLVM_INCLUDE_DIRS})

set(BUILD_TESTS, 0)

add_subdirectory(src)

if (${BUILD_TESTS} EQUAL 1)
    # Includes Catch in the project:
    add_subdirectory(cmake/ExternalProjects/catch)
    include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
    enable_testing(true)  # Enables unit-testing.

    add_subdirectory(tests)
endif()

