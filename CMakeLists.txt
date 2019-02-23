cmake_minimum_required(VERSION 2.8)

project(graphics)

include_directories(include)

add_subdirectory(src)

add_compile_options(-std=c++17 -Wall -Wextra -g)

#aux_source_directory(src DIR_SRCS)

add_executable(rt_test main.cpp)

target_link_libraries(rt_test graphics)
