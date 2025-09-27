#ifndef BBXX_H
#define BBXX_H

#include <SDL3/SDL.h>

#include <BBXX/WindowState.h>
#include <BBXX/GLState.h>
#include <BBXX/InputState.h>
#include <BBXX/ImGuiState.h>
#include <BBXX/AudioState.h>
#include <BBXX/FileSystemState.h>
#include <BBXX/ScreenState.h>

#include <BEATBOXX/BXCTX.h>

struct BBXX
{
    /* STATE CLASSES */

    WindowState windowstate;
    GLState glstate;
    InputState inputstate;
    ImGuiState imguistate;
    AudioState audiostate;
    FileSystemState filesystemstate;
    ScreenState screenstate;
    
    BXCTX bxctx { inputstate };
    
    /* PUBLIC METHODS */

    SDL_AppResult init();
    void iterate();
    void draw();
    SDL_AppResult handle_event(const SDL_Event* event);
    void quit();
}; // BBXX

#endif // BBXX