#include <BEATBOXX/ScreenState/Screen.h>

bool Screen::ScreenState__inits()
{
    return init();
}

void Screen::ScreenState__handles_event(const SDL_Event* event)
{
    return handle_event(event);
}

void Screen::ScreenState__iterates()
{
    iterate();
}

void Screen::ScreenState__draws()
{
    // TODO: implement glScissor() regioning stuff 
    
    draw();
}