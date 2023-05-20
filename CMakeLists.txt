cmake_minimum_required(VERSION 3.0)
project(tinc)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -pedantic-errors)
include_directories(${PROJECT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(SRCS
    src/ast.c
    src/compiler.c
    src/lexer.c
    src/parser.c
    src/preprocessor.c
    src/scanner.c
    src/string.c
    src/token.c
    src/vector.c)
set(MAIN_SRCS
    src/main.c ${SRCS})
set(TEST_SRCS
    test/ast.c
    test/hash.c
    test/main.c
    test/preprocessor.c
    test/string.c
    test/vector.c
    ${SRCS})

add_executable(tinc ${MAIN_SRCS})
set_property(TARGET tinc PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET tinc PROPERTY C_STANDARD 90)

# Tests
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(ExternalProject)
    ExternalProject_Add(
        ctest
        GIT_REPOSITORY https://github.com/bvdberg/ctest
        PREFIX ctest
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        UPDATE_DISCONNECTED TRUE
        )
    ExternalProject_Get_property(ctest SOURCE_DIR)

    list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")

    # Add tests
    enable_testing()

    add_executable(tinc_tests ${TEST_SRCS})
    include_directories(${SOURCE_DIR})
    add_test(test tinc_tests)
endif()
