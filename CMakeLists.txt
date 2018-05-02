cmake_minimum_required(VERSION 3.10)
project(OpenImageFilter)

set(CMAKE_CXX_STANDARD 11)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(OpenImageFilter src/main.cpp src/Bitmap.cpp src/Bitmap.h src/Color.h src/Logger.cpp src/Logger.h src/Filter.cpp src/Filter.h src/Kernels.h)