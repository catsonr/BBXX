#include <BBXX/GLState.h>

#ifndef __EMSCRIPTEN__
#include <glad/gl.h>
#else
#include <GLES3/gl3.h>
#endif

#include <stdio.h>

bool GLState::init(SDL_Window* window)
{
#ifndef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
    
    gl = SDL_GL_CreateContext(window);
    if( !gl ) {
        printf("[GLState::init] SDL failed to create gl context!\n");
        return false;
    }
    
#ifndef __EMSCRIPTEN__
        if( !gladLoaderLoadGL() ) {
        printf("[GLState::init] gladLoaderLoadGL() failed!\n");
        return false;
    }
#endif

    return true;
}

void GLState::draw(SDL_Window* window, int w, int h)
{
    glViewport(0, 0, w, h);
    glClearColor(0.2, 0.2, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}