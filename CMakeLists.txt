cmake_minimum_required(VERSION 3.12)
project(SLN_MetaData)

# gcc/g++编译选项设置
add_compile_options(-std=c++11)
# add_definitions("-std=c++11")

# 全局编译宏定义
# add_definitions(-DCO_MACHINE_X64) # v3.12后，对于编译宏的定义，建议使用add_compile_definitions取代add_definitions
# add_definitions(-DCO_OS_LINUX)
add_compile_definitions(CO_MACHINE_X64)
add_compile_definitions(CO_OS_LINUX)

# 关键字定义
add_compile_definitions(__cdecl=)    #gcc x64调用惯例有自己的一套规定，针对__cdecl、__stdcall属性都忽略了
add_compile_definitions(__stdcall=)
# add_compile_definitions(__cdecl=__attribute__\(\(cdecl\)\) __stdcall=__attribute__\(\(stdcall\)\))

# set(CMAKE_BUILD_TYPE "Debug")

# 项目
add_subdirectory(MetaData_Linux)
add_subdirectory(MetaDataPrj_Linux)