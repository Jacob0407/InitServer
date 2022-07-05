# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

include_directories($ENV{BOOST_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
link_directories($ENV{BOOST_LIBRARY_DIR})

project ("InitServer")

# 包含子项目。
# add_subdirectory ("InitServer")

# 将源代码添加到此项目的可执行文件。
add_executable (InitServer "InitServer/InitServer.cpp" "InitServer/InitServer.h" "common/Connection.h" "common/Connection.cpp")
add_executable (InitClient "InitClient/InitClient.cpp" "InitClient/InitClient.h" "common/Connection.h" "common/Connection.cpp")