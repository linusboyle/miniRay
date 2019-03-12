cmake_minimum_required(VERSION 3.2)

project(graphics)

include_directories(include)
add_compile_options(-Wall -Wextra)

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)

enable_testing()
add_test(NAME buildtest COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target rt_test)
add_test(NAME test COMMAND rt_test)

SET_TESTS_PROPERTIES(test PROPERTIES DEPENDS buildtest)