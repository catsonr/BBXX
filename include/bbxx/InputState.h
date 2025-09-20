#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL3/SDL.h>

struct InputState
{
    /* PUBLIC MEMBERS */
    
    /* what keyboard keys are currently pressed */
    bool keys[SDL_SCANCODE_COUNT] { false };
    /*
        what keyboard keys were pressed last frame 
        used to determine if a key was pressed/released this frame
    */
    bool keys_previous[SDL_SCANCODE_COUNT] { false };
    
    /*
        which mouse buttons are currently pressed
        SDL defines mouse buttons as:
            SDL_BUTTON_LEFT     1
            SDL_BUTTON_MIDDLE   2
            SDL_BUTTON_RIGHT    3
            SDL_BUTTON_X1       4
            SDL_BUTTON_X2       5
    */
    bool mouse_buttons[6] { false };
    /* which mouse buttons were pressed last frame */
    bool mouse_buttons_previous[6] { false };
    
    /* mouse position */
    unsigned mouse_x, mouse_y;

    /* change in scroll amount, cumulative */
    float scroll_vertical, scroll_horizontal;

    /* PUBLIC METHODS */

    void iterate();
    void handle_event(const SDL_Event* event);
    bool key_down(SDL_Scancode sc) const; // if given key is currently pressed
    bool key_pressed(SDL_Scancode sc) const; // if given key was pressed this frame
    bool key_released(SDL_Scancode sc) const; // if given key was released this frame
    bool mouse_down(SDL_MouseButtonFlags button) const; // if given mouse button is currently pressed
    bool mouse_pressed(SDL_MouseButtonFlags button) const; // if given mouse button was pressed this frame
    bool mouse_released(SDL_MouseButtonFlags button) const; // if given mouse button was released this frame
}; // InputState

#endif // INPUTSTATE_H