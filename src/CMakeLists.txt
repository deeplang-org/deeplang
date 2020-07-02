# -*- mode:cmake -*-
if(NOT UNIX)
  message(WARNING "Unsupported operating system")
endif()

set(antlr4-demo-GENERATED_SRC
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexer.cpp 
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexer.cpp
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexerBaseListener.cpp
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexerBaseVisitor.cpp
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexerListener.cpp
   ${PROJECT_SOURCE_DIR}/src/gen/DLLexerVisitor.cpp
 )

foreach(src_file ${antlr4-demo-GENERATED_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          GENERATED TRUE
          )
endforeach(src_file ${antlr4-demo-GENERATED_SRC})

add_custom_target(GenerateParser DEPENDS ${antlr4-demo-GENERATED_SRC})
add_custom_command(OUTPUT ${antlr4-demo-GENERATED_SRC}
   COMMAND 
   ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/src/gen/
   COMMAND
   "${Java_JAVA_EXECUTABLE}" -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -listener -visitor -o ${PROJECT_SOURCE_DIR}/src/gen/ -package antlrcpptest ${PROJECT_SOURCE_DIR}/demo/DLLexer.g4 ${PROJECT_SOURCE_DIR}/demo/DLLexer.g4
   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
   DEPENDS ${PROJECT_SOURCE_DIR}/demo/DLLexer.g4 ${PROJECT_SOURCE_DIR}/demo/DLLexer.g4
   )

include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/misc
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/atn
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/dfa
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/support
  ${PROJECT_SOURCE_DIR}/src/gen
  )

#file(GLOB antlr4-demo_SRC "${PROJECT_SOURCE_DIR}/src/gen/*")
set(antlr4-demo_SRC 
  ${PROJECT_SOURCE_DIR}/demo/Linux/main.cpp
  ${antlr4-demo-GENERATED_SRC}
  )

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set (flags_1 "-Wno-overloaded-virtual")
else()
  set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${antlr4-demo_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
          )
endforeach(src_file ${antlr4-demo_SRC})

add_executable(antlr4-demo
  ${antlr4-demo_SRC}
  )
#add_precompiled_header(antlr4-demo ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/antlrcpp-Prefix.h)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(antlr4-demo PRIVATE "/MT$<$<CONFIG:Debug>:d>")
endif()

add_dependencies(antlr4-demo GenerateParser)

target_link_libraries(antlr4-demo antlr4_static)

install(TARGETS antlr4-demo 
        DESTINATION "share" 
        COMPONENT dev 
        )

