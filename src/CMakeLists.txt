aux_source_directory(. DIR_SRCS)

add_compile_options(-Werror)

add_library(graphics ${DIR_SRCS})
target_compile_features(graphics PRIVATE cxx_std_17)
