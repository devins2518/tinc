cmake_minimum_required(VERSION 3.0)
project(tinc)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 98)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -pedantic-errors)
include_directories(${PROJECT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(SRCS
    src/ast.c
    src/compiler.c
    src/lexer.c
    src/preprocessor.c
    src/scanner.c
    src/string.c
    src/token.c
    src/vector.c)
set(MAIN_SRCS
    src/main.c ${SRCS})
set(TEST_SRCS
    test/hash.cpp
    test/preprocessor.cpp
    test/string.cpp
    # test/test_main.c
    # test/test_preprocessor.c
    # test/test_types.c
    test/vector.cpp
    ${SRCS})

add_executable(tinc ${MAIN_SRCS})

# Tests
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # GTest - testing library
    include(FetchContent)
    # v1.13.0
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_compile_definitions(CMAKE_TXT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

    enable_testing()

    add_executable(tinc_tests ${TEST_SRCS})
    target_link_libraries(tinc_tests GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tinc_tests)
endif()
