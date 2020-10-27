project(DeepLangVM)


aux_source_directory(./ VM_SRC)

add_library(dp_vm STATIC ${VM_SRC})

target_include_directories(dp_vm
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )



