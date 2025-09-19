#include <stdio.h>

#include <bbxx/BBXX.h>

SDL_AppResult BBXX::init()
{
    SDL_InitFlags initflags =
        SDL_INIT_AUDIO;
    if( !SDL_InitSubSystem(initflags) )
    {
        printf("[BBXX::init] failed to initialize subsystem(s)!\n%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH_INITIAL, WINDOW_HEIGHT_INITIAL, windowflags);
    if( !window )
    {
        printf("[BBXX::init] failed to create window!\n%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    printf("[BBXX::init] initialization successful!\n");

    return SDL_APP_CONTINUE;
}

void BBXX::iterate()
{

}

void BBXX::draw()
{

}

SDL_AppResult BBXX::handle_event(const SDL_Event* event)
{
    if ( event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED )
    {
        printf("[BBXX::handle_event] window close requested!\n");
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void BBXX::quit()
{
    printf("[BBXX::quit] quitting app ...\n");
}