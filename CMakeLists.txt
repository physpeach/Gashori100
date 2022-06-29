cmake_minimum_required(VERSION 3.16)

project(gashori CXX)

# OpenCVをリンク
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBRARIES})
message("include directories: ${OpenCV_INCLUDE_DIRS}")
message("include libraries  : ${OpenCV_LIBRARIES}\n")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-O3 -Wall)

add_subdirectory(q_001_010)