cmake_minimum_required(VERSION 3.14)
project(Deeplang)
set(CMAKE_CXX_STANDARD 14)


include_directories(
        ${PROJECT_SOURCE_DIR}/generated/
        ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/
        ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/src
        ${PROJECT_SOURCE_DIR}/src/parsers/
        ${PROJECT_SOURCE_DIR}/src/parsers/gen/
)

set(src_dir
        ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLLexer.cpp
        ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParser.cpp
        ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParserVisitor.cpp
        ${PROJECT_SOURCE_DIR}/src/parsers/gen/DLParserBaseVisitor.cpp
)

file(GLOB antlr_runtime_src
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/atn/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/dfa/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/misc/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/support/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/pattern/*.cpp
    ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/xpath/*.cpp
)

add_library (antlr_runtime ${antlr_runtime_src})
add_executable(DeepParser ${src_dir} src/main.cpp)
target_link_libraries(DeepParser antlr_runtime)