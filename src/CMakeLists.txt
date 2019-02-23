include_directories(../include)

add_compile_options(-std=c++17)

aux_source_directory(. DIR_SRCS)

add_library(graphics ${DIR_SRCS})
