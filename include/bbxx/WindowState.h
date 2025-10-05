#ifndef WINDOWSTATE_H
#define WINDOWSTATE_H

#include <SDL3/SDL.h>

#define SET_MINIMUM_WINDOW_SIZE_ON_INIT 0
#define ALWAYS_ON_TOP 0

struct WindowState
{
    /* PUBLIC MEMBERS */
    
    SDL_Window* window { nullptr };

    const int WINDOW_WIDTH_INITIAL { 1280 };
    const int WINDOW_HEIGHT_INITIAL { 720 };
    const int WINDOW_WIDTH_MIN  { 800 };
    const int WINDOW_HEIGHT_MIN { 600 };
    const char* WINDOW_TITLE { "BBXX game engine <3" };
    const SDL_WindowFlags windowflags =
        //SDL_WINDOW_FULLSCREEN |
        ALWAYS_ON_TOP ? SDL_WINDOW_ALWAYS_ON_TOP : 0 |
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_HIGH_PIXEL_DENSITY |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_INPUT_FOCUS |
        SDL_WINDOW_MOUSE_FOCUS
    ;
    
    /* whether or not BBXX is fullscreen */
    bool is_fullscreen { false };

    /* the actual dimensions of the window */
    int w, h;
    /*
        the logical dimensions of the window
        i.e., ignoring display scale 
    */
    int w_l, h_l;
    /*
        the window display scale
        most screens will have a display scale of 1.0, however high dpi screens will have >1.0
        (see: https://wiki.libsdl.org/SDL3/README-highdpi)
    */
    float ds;
    
    /* PUBLIC METHODS */

    bool init();
    void iterate();
    /* 
        toggles full screen 
        TODO:
            SDL's fullscreen by default is just borderless windowed fullscreen, support actual fullscreen in future
            (see: https://wiki.libsdl.org/SDL3/SDL_SetWindowFullscreenMode)
    */
    void fullscreen();
}; // WindowState

#endif // WindowState