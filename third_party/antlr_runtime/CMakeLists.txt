
file(GLOB libantlrcpp_SRC
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/atn/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/dfa/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/misc/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/support/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/pattern/*.cpp"
  "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/xpath/*.cpp"
)

add_library(antlr4_static STATIC ${libantlrcpp_SRC})

target_include_directories(antlr4_static
  PUBLIC
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime
  PRIVATE  
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/atn
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/dfa
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/misc
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/support
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/pattern
  ${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/tree/xpath
  )

#add_dependencies(antlr4_static make_lib_output_dir)

if(WIN32)
  target_compile_definitions(antlr4_static
    PUBLIC ANTLR4CPP_STATIC
    )
  set(static_lib_suffix "-static")
endif(WIN32)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_link_libraries(antlr4_static ${UUID_LIBRARIES})
elseif(APPLE)
  target_link_libraries(antlr4_static ${COREFOUNDATION_LIBRARY})
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  target_compile_options(antlr4_static
    PRIVATE
    /wd4251
    /wd4819
    /MP
    )
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  target_compile_options(antlr4_static
    PRIVATE
    -Wno-overloaded-virtual 
    -Wno-dollar-in-identifier-extension 
    -Wno-four-char-constants
    )
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "INTEL")
  target_compile_options(antlr4_static
    PRIVATE
    -Wno-overloaded-virtual
    -Wno-multichar
    )
endif()

set_target_properties(antlr4_static
                      PROPERTIES VERSION   ${ANTLR_VERSION}
                                 SOVERSION ${ANTLR_VERSION}
                                 OUTPUT_NAME "antlr4-runtime${static_lib_suffix}"
                                 #ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
                                 COMPILE_FLAGS "${disabled_compile_warnings} ${extra_static_compile_flags}")

install(TARGETS antlr4_static
        DESTINATION lib
        EXPORT antlr4-targets)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/third_party/antlr_runtime/" 
        DESTINATION "include/antlr4-runtime"
        COMPONENT dev 
        FILES_MATCHING PATTERN "*.h"
        )
