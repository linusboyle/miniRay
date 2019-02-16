include_directories(../include)

add_compile_options(-std=c++17)

aux_source_directory(. DIR_SRCS)

add_library(miniray ${DIR_SRCS})
