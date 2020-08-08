cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)
set(CMAKE_CXX_STANDARD 14)


option(DEEPLANG_TESTS "Build GTest-based tests" OFF)
option(DEEPLANG_ANTLR4_GEN "Use Anltr4 generate codes" ON)


if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

endif()

# generate parser lexer parser from g4
if (DEEPLANG_ANTLR4_GEN)
    execute_process(COMMAND 
        antlr4
        -Werror -Dlanguage=Cpp -listener -visitor
        -lib src/parsing
        src/parsing/DLLexer.g4
        src/parsing/DLParser.g4
        -o gen
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_executable(DeepParser src/main.cpp)

target_include_directories(DeepParser 
    PRIVATE
    gen/
    third_party/antlr_runtime/
    third_party/antlr_runtime/src
    )

target_sources(DeepParser 
    PRIVATE
    gen/DLLexer.cpp
    gen/DLParser.cpp
    gen/DLParserVisitor.cpp
    gen/DLParserBaseVisitor.cpp
    )

# Link antlr_runtime
add_subdirectory(third_party/antlr_runtime)
target_link_libraries(DeepParser antlr4_static)

# Link wabt
option(BUILD_TESTS "Don't need wabt test" OFF)
option(BUILD_TOOLS "Don't need wabt binary tools" OFF)
option(BUILD_LIBWASM "Don't need wabt shared library" OFF)
add_subdirectory(third_party/wabt)
target_link_libraries(DeepParser wabt)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_SOURCE_DIR}/third_party/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(third_party/googletest-src
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${gtest_SOURCE_DIR}/include")


add_executable(cctest test/cctest/cctest.cc)

target_include_directories(cctest 
    PRIVATE
    gen/
    third_party/antlr_runtime/
    third_party/antlr_runtime/src
    third_party/googletest-src/googletest/include/gtest
    )

target_sources(cctest 
    PRIVATE
    gen/DLLexer.cpp
    gen/DLParser.cpp
    gen/DLParserVisitor.cpp
    gen/DLParserBaseVisitor.cpp
)
target_link_libraries(cctest antlr4_static gtest_main)

