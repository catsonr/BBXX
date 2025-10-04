cmake_minimum_required(VERSION 3.16)

project(minimal_bbxx_example)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(jukebox main.cpp)
target_link_libraries(jukebox PRIVATE BBXX)

target_compile_definitions(jukebox PRIVATE ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(EMSCRIPTEN)
    target_link_options(jukebox PRIVATE --preload-file ${ASSETS_DIR}@assets)
endif()
