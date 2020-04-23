cmake_minimum_required(VERSION 3.4)
project(CCP_Demo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp dummy.cpp)
add_executable(hello ${SOURCE_FILES})