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

    if( SET_MINIMUM_WINDOW_SIZE_ON_INIT )
        SDL_SetWindowMinimumSize(window, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);

    return true;
}

void WindowState::iterate()
{
    SDL_GetWindowSizeInPixels(window, &w, &h);
    SDL_GetWindowSize(window, &w_l, &h_l);
    ds = SDL_GetWindowDisplayScale(window);
    
    //printf("w=%d h=%d\nw_l=%dh_l=%d (ds=%f)\n", w, h, w_l, h_l, ds);
}

void WindowState::fullscreen()
{
    if( SDL_SetWindowFullscreen(window, !is_fullscreen) )
        is_fullscreen = !is_fullscreen;
    else 
        printf("[WindowState::fullscreen] failed to enter/exit full screen! ignoring ...\n");
}