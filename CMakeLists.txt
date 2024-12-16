cmake_minimum_required(VERSION 3.10)
project(my_mp4_parser VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(googletest)
