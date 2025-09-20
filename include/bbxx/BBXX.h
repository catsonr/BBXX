#ifndef BBXX_H
#define BBXX_H

#include <SDL3/SDL.h>

#include <BBXX/WindowState.h>
#include <BBXX/GLState.h>
#include <BBXX/InputState.h>

struct BBXX
{
    /* STATE CLASSES */

    WindowState windowstate;
    GLState glstate;
    InputState inputstate;
    
    /* PUBLIC METHODS */

    SDL_AppResult init();
    void iterate();
    void draw();
    SDL_AppResult handle_event(const SDL_Event* event);
    void quit();
}; // BBXX

#endif // BBXX