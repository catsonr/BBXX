#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <BBXX/BBXX.h>
BBXX bbxx;
float t = 0.0f;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    bbxx.init();
    
    // create shader program
    bbxx.glstate.shaderprograms.emplace_back( "shaders/shaderprogram.vert", "shaders/shaderprogram.frag" );
    bbxx.glstate.shaderprograms.back().init(bbxx.filesystemstate);
    
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
    bbxx.iterate();
    
    bbxx.glstate.shaderprograms.back().set_uniform("u_t", t);
    t += 0.001f;

    bbxx.draw();

    // return SDL_APP_SUCCESS to go to SDL_AppQuit()
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    bbxx.quit();
}