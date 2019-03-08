cmake_minimum_required(VERSION 2.8)

project(graphics)

include_directories(include)
add_compile_options(-Wall -Wextra)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME test COMMAND rt_test)
