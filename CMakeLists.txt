cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)
set(CMAKE_CXX_STANDARD 14)


if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

endif()

# generate parser lexer parser from g4
execute_process(COMMAND 
    antlr4
    -Werror -Dlanguage=Cpp -listener -visitor
    ${PROJECT_SOURCE_DIR}/src/parsing/DLLexer.g4
    ${PROJECT_SOURCE_DIR}/src/parsing/DLParser.g4
    -o ${PROJECT_SOURCE_DIR}/gen)





add_executable(DeepParser src/main.cpp)

target_include_directories(DeepParser 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gen/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/src
    )

target_sources(DeepParser 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gen/DLLexer.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParser.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParserVisitor.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParserBaseVisitor.cpp
)


add_subdirectory(third_party/antlr_runtime)
target_link_libraries(DeepParser antlr4_static)




# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${gtest_SOURCE_DIR}/include")


add_executable(cctest test/cctest/cctest.cc)

target_include_directories(cctest 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gen/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src/googletest/include/gtest
    )

target_sources(cctest 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gen/DLLexer.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParser.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParserVisitor.cpp
    ${PROJECT_SOURCE_DIR}/gen/DLParserBaseVisitor.cpp
)
target_link_libraries(cctest antlr4_static gtest_main)
