#include <BBXX/ScreenState.h>

bool ScreenState::init()
{
    bool failed = false;
    
    int screen_count = screens.size();

    printf("[ScreenState::init] initializing %d screen(s) ...\n", screen_count);
    
    for( const auto& screen : screens )
    {
        int i = 1;
        if( !screen->ScreenState__inits() )
        {
            printf("\t[%d/%d] failed to initialize screen '%s'\n", i, screen_count, screen->name);
            failed = true;
            break;
        }
        else
        {
            printf("\t[%d/%d] initialized '%s'\n", i, screen_count, screen->name);
        }
        
        i++;
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