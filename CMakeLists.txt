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
    src/preprocessor.c
    src/scanner.c
    src/string.c
    src/token.c
    src/vector.c)
set(MAIN_SRCS
    src/main.c ${SRCS})
set(TEST_SRCS
    test/hash.c
    test/preprocessor.c
    test/string.c
    test/vector.c
    ${SRCS})

add_executable(tinc ${MAIN_SRCS})
set_property(TARGET tinc PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET tinc PROPERTY C_STANDARD 90)

# Tests
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(PkgConfig)
    
    find_path(CRITERION_INCLUDE_DIR criterion/criterion.h
              PATH_SUFFIXES criterion)
    
    find_library(CRITERION_LIBRARY NAMES criterion libcriterion)
    
    set(CRITERION_LIBRARIES ${CRITERION_LIBRARY})
    set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})
    
    include(FindPackageHandleStandardArgs)
    # handle the QUIET and REQUIRED arguments and set CRITERION_FOUND to TRUE
    # if all listed variables are TRUE
    find_package_handle_standard_args(Criterion DEFAULT_MSG
                                      CRITERION_LIBRARY CRITERION_INCLUDE_DIR)
    
    mark_as_advanced(CRITERION_INCLUDE_DIR CRITERION_LIBRARY)

    list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")

    # Add tests
    enable_testing()

    add_executable(tinc_tests ${TEST_SRCS})
    include_directories(${CRITERION_INCLUDE_DIRS})
    target_link_libraries(tinc_tests ${CRITERION_LIBRARIES})
    add_test(tinc_tests tinc_tests)
endif()
