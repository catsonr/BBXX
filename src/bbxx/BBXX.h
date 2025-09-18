#ifndef BBXX_H
#define BBXX_H

#include <SDL3/SDL.h>

struct BBXX
{
    /* PUBLIC MEMBERS */
    
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer { nullptr };

    const int WINDOW_WIDTH_INITIAL { 1280 };
    const int WINDOW_HEIGHT_INITIAL { 720 };
    const int WINDOW_WIDTH_MIN  { 800 };
    const int WINDOW_HEIGHT_MIN { 600 };
    const char* WINDOW_TITLE { "BBXX game engine :)" };
    SDL_WindowFlags windowflags =
        //SDL_WINDOW_FULLSCREEN |
        //SDL_WINDOW_ALWAYS_ON_TOP |
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_HIGH_PIXEL_DENSITY |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_INPUT_FOCUS |
        SDL_WINDOW_MOUSE_FOCUS
    ;
    
    /* PUBLIC METHODS */

    SDL_AppResult init();
    void iterate();
    void draw();
    SDL_AppResult handle_event(const SDL_Event* event);
    void quit();
}; // BBXX

#endif // BBXX