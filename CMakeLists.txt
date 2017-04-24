cmake_minimum_required(VERSION 3.7)
project(MyVector)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Vector.h)
add_executable(MyVector ${SOURCE_FILES})