cmake_minimum_required(VERSION 2.8)

project(miniRay)

include_directories(include)

add_subdirectory(src)

add_compile_options(-std=c++17)

#aux_source_directory(src DIR_SRCS)

add_executable(render main.cpp)

target_link_libraries(render miniray)
