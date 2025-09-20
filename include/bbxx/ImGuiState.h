#ifndef IMGUISTATE_H
#define IMGUISTATE_H

#include <SDL3/SDL.h>

struct ImGuiState
{
    /* PUBLIC METHODS */
    
    bool init(SDL_Window* window, SDL_GLContext gl);
    void handle_event(const SDL_Event* event);
    void draw();

}; // ImGuiState

#endif // ImGuiState