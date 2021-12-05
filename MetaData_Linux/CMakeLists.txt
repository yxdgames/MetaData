cmake_minimum_required(VERSION 3.12)

project(MetaData)

# gcc/g++编译选项设置
add_compile_options(-fPIC)
add_compile_options(-fvisibility=hidden)
# add_definitions("-fvisibility=hidden")

# 预编译宏定义
add_compile_definitions(CO_METADATA_KERNEL_DLL_EXPORTS)
add_compile_definitions(CO_SERIALIZATION_MODULE)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(__META_DATA_DEMO__)
endif()

message(STATUS "CMake top source directory: " ${CMAKE_SOURCE_DIR})
message(STATUS "CMake current source directory: " ${CMAKE_CURRENT_SOURCE_DIR})

set(CODE_ROOT ${CMAKE_SOURCE_DIR}/Codes)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CODE_ROOT}/include)
# include_directories(${CODE_ROOT}/MetaData/include)
# include_directories(${CODE_ROOT}/Serialization/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LST)
aux_source_directory(${CODE_ROOT}/src SL_BS)
aux_source_directory(${CODE_ROOT}/MetaData/src SL_MD)
aux_source_directory(${CODE_ROOT}/Serialization/src SL_SE)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    aux_source_directory(${CODE_ROOT}/MetaData/src/Demo SL_DEMO)
endif()

list(APPEND SRC_LST ${SL_BS})
list(APPEND SRC_LST ${SL_MD})
list(APPEND SRC_LST ${SL_SE})
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    list(APPEND SRC_LST ${SL_DEMO})
endif()
list(REMOVE_ITEM SRC_LST ${CODE_ROOT}/src/MetaDataObjects.cpp)

# message("Sources: " ${SRC_LST})

add_library(${PROJECT_NAME} SHARED ${SRC_LST})
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)