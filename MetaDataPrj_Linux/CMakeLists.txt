cmake_minimum_required(VERSION 3.12)

project(MetaDataPrj)

add_compile_definitions(CO_METADATA_KERNEL_DLL_IMPORTS)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(__META_DATA_DEMO__)
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LST)

# message("Sources: " ${SRC_LST})

add_executable(${PROJECT_NAME} ${SRC_LST})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(${PROJECT_NAME} -lMetaData)