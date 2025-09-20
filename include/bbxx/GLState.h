#ifndef GLSTATE_H
#define GLSTATE_H

#include <SDL3/SDL.h>

struct GLState
{
    /* PUBLIC MEMBERS */
    
    SDL_GLContext gl { nullptr };
    
    /* PUBLIC METHODS */

    bool init(SDL_Window* window);
    void draw(SDL_Window* window, int w, int h);
}; // GLState

#endif // GLState