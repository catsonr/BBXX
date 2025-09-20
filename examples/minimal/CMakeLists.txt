cmake_minimum_required(VERSION 3.16)

project(minimal_bbxx_example)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minimal main.cpp)
target_link_libraries(minimal PRIVATE BBXX)

if(EMSCRIPTEN)
    set_target_properties(minimal PROPERTIES SUFFIX ".html")
    
    target_link_options(minimal PRIVATE
        #"-sUSE_SDL=3"
        "-sMIN_WEBGL_VERSION=2"
        "-sMAX_WEBGL_VERSION=2"
        #"-sALLOW_MEMORY_GROWTH=1"
    )
endif()