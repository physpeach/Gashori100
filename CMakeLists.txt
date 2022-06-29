cmake_minimum_required(VERSION 3.16)

project(gashori CXX)

# OpenCVをリンク
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message("include directories: ${OpenCV_INCLUDE_DIRS}")
message("include libraries  : ${OpenCV_LIBRARIES}\n")

add_subdirectory(q_001_010)