# 000
add_executable(q000 000_hello_world.cpp)
target_compile_features(q000 PUBLIC cxx_std_17)
target_compile_options(q000 PUBLIC -O3 -Wall)
target_link_libraries(q000 ${OpenCV_LIBRARIES})