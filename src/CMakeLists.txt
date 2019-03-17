aux_source_directory(. DIR_MAIN_SRCS)
aux_source_directory(raster DIR_RASTER_SRCS)

find_package(OpenCV REQUIRED)

add_compile_options(-Werror)

add_library(graphics ${DIR_MAIN_SRCS} ${DIR_RASTER_SRCS})
target_link_libraries(graphics ${OpenCV_LIBS})
target_compile_features(graphics PRIVATE cxx_std_17)
