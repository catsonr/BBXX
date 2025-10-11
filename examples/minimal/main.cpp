#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <BBXX/BBXX.h>
BBXX bbxx;
glm::mat4 model { 1.0f };
float t { 0.0f };

#include <glm/ext.hpp>

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if( bbxx.init() == SDL_APP_FAILURE ) return SDL_APP_FAILURE;
    
    // create shader program
    bbxx.glstate.shaderprograms.emplace_back( "shaders/shaderprogram.vert", "shaders/shaderprogram.frag" );
    ShaderProgram& shaderprogram = bbxx.glstate.shaderprograms.back();

    // initialize shader program
    shaderprogram.init(bbxx.filesystemstate);
    
    // set shader program uniforms
    shaderprogram.uniform_attach("u_mVP", &bbxx.glstate.m_VP);
    shaderprogram.uniform_attach("u_mModel", &model);
    shaderprogram.uniform_attach("u_t", &t);
    shaderprogram.set_uniforms();
    
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return bbxx.handle_event(event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    model = glm::scale({ 1.0f }, glm::vec3(bbxx.windowstate.h / 4, bbxx.windowstate.h / 4, 1.0));

    bbxx.iterate();
    bbxx.draw();
    
    t += 0.01;

    // return SDL_APP_SUCCESS to go to SDL_AppQuit()
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    bbxx.quit();
}