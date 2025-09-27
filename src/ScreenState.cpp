#include <BBXX/ScreenState.h>

bool ScreenState::init()
{
    bool failed = false;
    
    for( const auto& screen : screens )
    {
        if( !screen->ScreenState__inits() )
        {
            printf("[ScreenState::init] failed to initialize (a) screen\n");
            failed = true;
            break;
        }
    }
    
    if( failed ) printf("[ScreenState::init] failed to initialize all screens!\n");
    
    return !failed;
}

SDL_AppResult ScreenState::handle_event(const SDL_Event* event)
{
    for( const auto& screen : screens )
    {
        screen->ScreenState__handles_event(event);
    }
    
    return SDL_APP_CONTINUE;
}

void ScreenState::iterate()
{
    for( const auto& screen : screens )
    {
        screen->ScreenState__iterates();
    }
}

void ScreenState::draw()
{
    for( const auto& screen : screens )
    {
        screen->ScreenState__draws();
    }
}