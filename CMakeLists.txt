cmake_minimum_required(VERSION 3.19)
project(cvv_tutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cvv_tutorial main.cpp)
target_link_libraries(cvv_tutorial
        opencv_core opencv_imgproc opencv_features2d opencv_cvv)