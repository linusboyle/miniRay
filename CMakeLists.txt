cmake_minimum_required(VERSION 2.8)

project(graphics)

include_directories(include)
add_compile_options(-std=c++17 -Wall -Wextra -Werror)

add_subdirectory(src)
add_subdirectory(test)
