cmake_minimum_required(VERSION 3.21)
project(CObject C)
project(CObjectTest C)

set(CMAKE_C_STANDARD 99)

add_library(CObject STATIC library.c)
add_executable(CObjectTest test.c)
target_link_libraries(CObjectTest CObject)
