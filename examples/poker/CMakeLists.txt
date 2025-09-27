cmake_minimum_required(VERSION 3.16)

project(poker_bbxx_example)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQURED ON)

add_executable(poker main.cpp)
target_link_libraries(poker PRIVATE BBXX)

if(EMSCRIPTEN)
    target_link_libraries(poker PRIVATE --preload-file ${CMAKE_CURRENT_SOURCE_DIR/assets@assets})
endif()