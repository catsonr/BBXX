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

# uncomment if using audio worklets
#if(EMSCRIPTEN)
#   add_compile_options(-matomics -mbulk-memory -pthread)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#endif()

# SDL3
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
target_link_libraries(BBXX PUBLIC SDL3::SDL3)

# glad
add_library(glad STATIC vendored/glad/src/gl.c)
target_include_directories(glad PUBLIC vendored/glad/include)
target_link_libraries(BBXX PUBLIC glad)

# imgui
file(GLOB IMGUI_SOURCES
    vendored/imgui/imgui.cpp
    vendored/imgui/imgui_draw.cpp
    vendored/imgui/imgui_tables.cpp
    vendored/imgui/imgui_widgets.cpp
    vendored/imgui/imgui_demo.cpp
    vendored/imgui/backends/imgui_impl_sdl3.cpp
    vendored/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC vendored/imgui vendored/imgui/backends)
target_link_libraries(imgui PRIVATE SDL3::SDL3 glad)
target_link_libraries(BBXX PUBLIC imgui)

# miniaudio
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE vendored/miniaudio)
target_link_libraries(BBXX PUBLIC miniaudio)

# glm
target_include_directories(BBXX PUBLIC vendored/glm)

# example targets
add_subdirectory(examples)

# emscripten flags
if(EMSCRIPTEN)
    set_target_properties(minimal PROPERTIES SUFFIX ".html")
    
    target_link_options(minimal PRIVATE
        "-sMIN_WEBGL_VERSION=2"
        "-sMAX_WEBGL_VERSION=2"
        #"-sALLOW_MEMORY_GROWTH=1"
        
        # audio worklets are better, but they cannot simply be statically hosted. so they'll be ignored for now
        #"-sAUDIO_WORKLET=1"
        #"-sWASM_WORKERS=1"
        #"-sASYNCIFY"
        #"-pthread"
        
        "-sWASMFS"
    )
    
endif()