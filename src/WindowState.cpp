#include <BBXX/WindowState.h>

#include <stdio.h>

bool WindowState::init()
{
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH_INITIAL, WINDOW_HEIGHT_INITIAL, windowflags);
    if( !window )
    {
        printf("[WindowState::init] failed to create window!\n%s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);

    return true;
}