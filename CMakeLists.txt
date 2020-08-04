cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)
set(CMAKE_CXX_STANDARD 14)


if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


add_executable(DeepParser src/main.cpp)

set_target_properties(DeepParser PROPERTIES
    OUTPUT_NAME  deepr
    )

target_include_directories(DeepParser 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/generated/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/src
    ${PROJECT_SOURCE_DIR}/src/parsers/
    ${PROJECT_SOURCE_DIR}/src/parsers/gen/
    )

target_sources(DeepParser 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLLexer.cpp
    ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParser.cpp
    ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParserVisitor.cpp
    ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParserBaseVisitor.cpp
)


add_subdirectory(third_party/antlr_runtime)
target_link_libraries(DeepParser antlr4_static)
