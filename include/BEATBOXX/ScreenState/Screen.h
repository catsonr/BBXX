#ifndef SCREEN_H
#define SCREEN_H

#include <SDL3/SDL.h>

#include <BEATBOXX/BXCTX.h>

struct Screen
{
    /* CONSTRUCTORS */
    Screen() = delete;
    Screen(const char* name, BXCTX& bxctx) :
        name(name),
        bxctx(bxctx)
    {}

    /* PUBLIC MEMBERS */
    
    const char* name;
    BXCTX& bxctx;

    /* PUBLIC METHODS */
    
    bool ScreenState__inits();
    void ScreenState__handles_event(const SDL_Event* event);
    void ScreenState__iterates();
    void ScreenState__draws();
    
    /* PRIVATE METHODS */

private:
    virtual bool init() { return true; }
    virtual void handle_event(const SDL_Event* event) {};
    virtual void iterate() {};
    virtual void draw() {};
}; // Screen

#endif // SCREEN_H