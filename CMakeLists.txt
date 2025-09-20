cmake_minimum_required(VERSION 3.16)
project(BBXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# BBXX
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_library(BBXX ${SOURCE_FILES})
target_include_directories(BBXX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# SDL3
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
target_link_libraries(BBXX PUBLIC SDL3::SDL3)

# glad
add_library(glad STATIC vendored/glad/src/gl.c)
target_include_directories(glad PUBLIC vendored/glad/include)
target_link_libraries(BBXX PUBLIC glad)

# example targets
# cmake --build build --target minimal
add_subdirectory(examples)