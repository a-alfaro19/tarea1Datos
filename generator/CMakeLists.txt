cmake_minimum_required(VERSION 3.28)
project(generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(generator main.cpp
        Generator.cpp
        Generator.h)
