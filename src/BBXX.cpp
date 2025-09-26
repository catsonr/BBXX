#include <stdio.h>

#include <BBXX/BBXX.h>

SDL_AppResult BBXX::init()
{
    SDL_InitFlags initflags =
        SDL_INIT_AUDIO;
    if( !SDL_InitSubSystem(initflags) )
    {
        printf("[BBXX::init] failed to initialize subsystem(s)!\n%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    // initialize state classes 
    if( !windowstate.init() ) return SDL_APP_FAILURE;
    if( !filesystemstate.init() ) return SDL_APP_FAILURE;
    if( !glstate.init(windowstate.window, filesystemstate) ) return SDL_APP_FAILURE;
    if( !imguistate.init(windowstate.window, glstate.gl) ) return SDL_APP_FAILURE;
    if( !audiostate.init() ) return SDL_APP_FAILURE;
    
    printf("[BBXX::init] initialization successful!\n");
    
    return SDL_APP_CONTINUE;
}

void BBXX::iterate()
{
    windowstate.iterate();
    audiostate.iterate();

    inputstate.iterate(); // should be called last
}

void BBXX::draw()
{
    glstate.draw(windowstate.window, windowstate.w, windowstate.h);
    imguistate.draw();

    SDL_GL_SwapWindow(windowstate.window);
}

SDL_AppResult BBXX::handle_event(const SDL_Event* event)
{
    if ( event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED )
    {
        printf("[BBXX::handle_event] window close requested!\n");
        return SDL_APP_SUCCESS;
    }
    
    inputstate.handle_event(event); // should be called first
    imguistate.handle_event(event);

    return SDL_APP_CONTINUE;
}

void BBXX::quit()
{
    filesystemstate.cleanup();

    printf("[BBXX::quit] quitting app ...\n");
}