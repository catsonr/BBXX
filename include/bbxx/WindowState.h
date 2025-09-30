#ifndef WINDOWSTATE_H
#define WINDOWSTATE_H

#include <SDL3/SDL.h>

#define SET_MINIMUM_WINDOW_SIZE_ON_INIT false
#define ALWAYS_ON_TOP false

struct WindowState
{
    /* PUBLIC MEMBERS */
    
    SDL_Window* window { nullptr };

    const int WINDOW_WIDTH_INITIAL { 1280 };
    const int WINDOW_HEIGHT_INITIAL { 720 };
    const int WINDOW_WIDTH_MIN  { 800 };
    const int WINDOW_HEIGHT_MIN { 600 };
    const char* WINDOW_TITLE { "BBXX game engine <3" };
    SDL_WindowFlags windowflags =
        //SDL_WINDOW_FULLSCREEN |
#ifdef ALWAYS_ON_TOP
        SDL_WINDOW_ALWAYS_ON_TOP |
#endif // ALWAYS_ON_TOP
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_HIGH_PIXEL_DENSITY |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_INPUT_FOCUS |
        SDL_WINDOW_MOUSE_FOCUS
    ;
    
    int w, h;
    int w_l, h_l;
    float ds;
    
    /* PUBLIC METHODS */

    bool init();
    void iterate();
}; // WindowState

#endif // WindowState