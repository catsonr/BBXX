#ifndef SCREENSTATE_H
#define SCREENSTATE_H

#include <SDL3/SDL.h>

#include <BEATBOXX/ScreenState/Screen.h>

#include <vector>
#include <memory>

struct ScreenState
{
    /* PUBLIC MEMBERS */
    
    std::vector<std::unique_ptr<Screen>> screens;
    
    /* PUBLIC METHODS */
    
    bool init();
    SDL_AppResult handle_event(const SDL_Event* event);
    void iterate();
    void draw();
}; // ScreenState

#endif // SCREENSTATE_H