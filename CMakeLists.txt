cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)


option(DEEPLANG_BUILD_TESTS "Build GTest-based tests" ON)
option(DEEPLANG_ANTLR4_GEN "Use Antlr4 generating parser codes" ON)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

if (UNIX)
	set(CMAKE_CXX_FLAGS "-pthread")
endif(UNIX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
else ()
endif()

# generate parser lexer parser from g4
if (DEEPLANG_ANTLR4_GEN)
    execute_process(
        COMMAND antlr4
                -Werror -Dlanguage=Cpp -listener -visitor
                -lib src/parsing
                src/parsing/DLLexer.g4
                src/parsing/DLParser.g4
                -o gen
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

function (deeplang_executable)
    cmake_parse_arguments(EXE "" "NAME" "SOURCES;INCLUDES;LIBS" ${ARGN})

    set(EXE_INCLUDES
        PRIVATE
        gen/
        src/
        third_party/
        ${WABT_SOURCE_DIR}
        ${WABT_BINARY_DIR}

        ${EXE_INCLUDES}
    )

    set(EXE_SOURCES
        gen/DLLexer.cpp
        gen/DLParser.cpp
        gen/DLParserVisitor.cpp
        gen/DLParserBaseVisitor.cpp

        src/ast/ast.h
        src/ast/ast.cpp
        src/ast/type.h
        src/ast/type.cpp
        src/codegen/codegen.h
        src/codegen/codegen.cpp
        src/parsing/parsing.cpp
        src/parsing/parsing.h
        src/utils/cast.h
        src/utils/error.h
        src/utils/error-formatter.h
        src/utils/error-formatter.cpp
        src/utils/result.h

        ${EXE_SOURCES}
    )

    set(EXE_LIBS
        antlr4_static
        wabt

        ${EXE_LIBS}
    )

    add_executable(${EXE_NAME} ${EXE_SOURCES})
    target_include_directories(${EXE_NAME} ${EXE_INCLUDES})
    target_link_libraries(${EXE_NAME} ${EXE_LIBS})
endfunction()


# Import antlr_runtime
add_subdirectory(third_party/antlr_runtime)

# Import wabt
option(BUILD_TESTS "Don't need wabt test" OFF)
option(BUILD_TOOLS "Don't need wabt binary tools" OFF)
option(BUILD_LIBWASM "Don't need wabt shared library" OFF)
add_subdirectory(third_party/wabt)

# deeplang compiler
deeplang_executable(
    NAME dp
    SOURCES src/main.cpp
)


if (DEEPLANG_BUILD_TESTS)
    find_package(PythonInterp 3.5)
    if (NOT PYTHONINTERP_FOUND)
        message(FATAL_ERROR "Python 3 is required for testing.")
    endif()
    # if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/googletest)
    #     message(FATAL_ERROR "Can't find third_party/googletest. Run git submodule update --init.")
    # endif()
    
    # gtest
    include_directories(
        third_party/googletest/googletest
        third_party/googletest/googletest/include
    )

    add_library(gtest STATIC
        third_party/googletest/googletest/src/gtest-all.cc
    )

    add_library(gtest_main STATIC
        third_party/googletest/googletest/src/gtest_main.cc
    )

    # tests
    deeplang_executable(
        NAME dp_cctest
        SOURCES test/cctest/cctest.cc
        LIBS gtest gtest_main
    )

    deeplang_executable(
        NAME dp_codegen
        SOURCES test/cctest/codegen.cc
        LIBS gtest gtest_main
    )
endif()
