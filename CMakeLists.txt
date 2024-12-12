cmake_minimum_required(VERSION 3.10)
project(my_mp4_parser VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)

add_executable(my_mp4_parser ${SRC_FILES})
