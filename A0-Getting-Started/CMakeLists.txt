cmake_minimum_required(VERSION 3.4)
project(A0_GETTING_STARTED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp x.cpp)
add_executable(hello ${SOURCE_FILES})