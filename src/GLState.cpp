#include <BBXX/GLState.h>

#include <BBXX/gl.h>

#include <glm/ext.hpp>

#include <stdio.h>

bool GLState::init(SDL_Window* window, FileSystemState& filesystemstate)
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

void GLState::iterate(const FileSystemState& filesystemstate)
{
    for( ShaderProgram& shaderprogram : shaderprograms)
    {
        if( shaderprogram.reload_requested )
        {
            shaderprogram.reload(filesystemstate);
        }
    }
}

void GLState::draw(SDL_Window* window, int w, int h, float ds)
{
    glViewport(0, 0, w, h);
    glClearColor(0.2, 0.2, 1.0, 1.0);
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*
       the above gl instructions begin drawing to the screen
       the below gl instructions make all shaderprograms run inside a white box,
       with origin at bottom left
       ahead of a blue background
    */

    int padding = 10 * ds;
    
    glViewport(padding, padding, w - padding*2, h - padding*2);
    glScissor(padding, padding, w - padding*2, h - padding*2);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // TEMP! each shaderprogram should have its own model matrix...
    glm::mat4 model { 1.0f };
    set_mVP(w - padding*2, h - padding*2);
    for( ShaderProgram& s : shaderprograms )
    {
        s.set_uniforms();
        s.draw();
    }
}

void GLState::set_mVP(int w, int h)
{
    //camera_aspect_ratio = static_cast<float>(w) / h;
    
    // perspective
    //m_view = glm::lookAt(camera_pos, camera_target, camera_up);
    //m_proj = glm::perspective(glm::radians(camera_fov), camera_aspect_ratio, camera_near, camera_far);

    // orthographic
    m_view = glm::mat4(1.0f);
    m_proj = glm::ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, -1.0f, 1.0f);
    //m_proj = glm::ortho(0.0f, w / 1.0f, 0.0f, h / 1.0f, -1.0f, 1.0f);
    
    m_VP = m_proj * m_view;
}