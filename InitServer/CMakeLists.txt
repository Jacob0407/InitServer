# CMakeList.txt: InitServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories($ENV{BOOST_INCLUDE_DIR})
include_directories($ENV{PYTHON_INCLUDE_DIR})
link_directories($ENV{BOOST_LIBRARY_DIR})
link_directories($ENV{PYTHON_LIBRARY_DIR})

# 将源代码添加到此项目的可执行文件。
add_executable (InitServer "InitServer.cpp" "InitServer.h")

# TODO: 如有需要，请添加测试并安装目标。
