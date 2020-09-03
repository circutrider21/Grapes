cmake_minimum_required(VERSION 3.10)

project(Grapes VERSION 1.0)

include_directories(AFTER include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Grapes main.cpp)