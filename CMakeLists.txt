cmake_minimum_required(VERSION 3.2)

project(graphics)

configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

option(USE_FLOAT
    "use float in computing" OFF)

include_directories(include ${PROJECT_BINARY_DIR})
add_compile_options(-Wall -Wextra)

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)

enable_testing()
add_test(NAME buildtest COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target rt_test)
add_test(NAME test COMMAND rt_test)

SET_TESTS_PROPERTIES(test PROPERTIES DEPENDS buildtest)
