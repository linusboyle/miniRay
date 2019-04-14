aux_source_directory(. TEST_SOURCE)

add_executable(rt_test ${TEST_SOURCE}) 

target_compile_features(rt_test PRIVATE cxx_std_17)
target_link_libraries(rt_test graphics)
target_link_libraries(rt_test stdc++fs)
target_link_libraries(rt_test gomp)