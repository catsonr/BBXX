cmake_minimum_required(VERSION 3.16)

project(minimal_bbxx_example)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minimal main.cpp)
target_link_libraries(minimal PRIVATE BBXX)
