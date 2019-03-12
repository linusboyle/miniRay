aux_source_directory(. DIR_SRCS)
find_package(OpenCV REQUIRED)

add_compile_options(-Werror)

add_library(graphics ${DIR_SRCS})
target_link_libraries(graphics ${OpenCV_LIBS})
target_compile_features(graphics PRIVATE cxx_std_17)
