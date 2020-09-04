cmake_minimum_required(VERSION 3.10)

project(Grapes VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

add_executable(Grapes main.cpp)

target_link_libraries(Grapes Core)