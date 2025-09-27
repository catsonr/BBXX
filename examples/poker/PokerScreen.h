#ifndef POKERSCREEN_H
#define POKERSCREEN_H

#include <BEATBOXX/ScreenState/Screen.h>

#include <stdio.h>

struct Poker
{

}; // Poker

struct PokerScreen : Screen
{
    /* CONSTRUCTORS */

    PokerScreen() = delete;
    PokerScreen(BXCTX& bxctx) :
        Screen(bxctx)
    {}
    
    /* PUBLIC MEMBERS */

    Poker poker;
    
    /* PUBLIC METHODS */

    bool init() override
    {
        printf("[PokerScreen::init] hello world :}\n");
        
        return true;
    }
    
    void handle_event(const SDL_Event* event) override
    {
        if( bxctx.inputstate.key_pressed(SDL_SCANCODE_SPACE) )
        {
            printf("[PokerScreen::handle_event] fyi space got pressed\n");
        }
    }
    
    void iterate() override
    {

    }
    
    void draw() override
    {
        // do nothing, for now
    }
}; // PokerScreen

#endif // POKERSCREEN_H