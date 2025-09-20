#include <BBXX/InputState.h>

#include <stdio.h>
#include <cstring>

void InputState::iterate()
{
    std::memcpy(keys_previous, keys, sizeof keys);
    std::memcpy(mouse_buttons_previous, mouse_buttons, sizeof mouse_buttons);
}

void InputState::handle_event(const SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_EVENT_KEY_DOWN:
            if( !event->key.repeat )
                keys[event->key.scancode] = true;
            //printf("%i pressed\n", event->key.scancode);
            break;

        case SDL_EVENT_KEY_UP:
            keys[event->key.scancode] = false;
            //printf("%i released\n", event->key.scancode);
            break;

        case SDL_EVENT_MOUSE_MOTION:
            mouse_x = event->motion.x;
            mouse_y = event->motion.y;
            //printf("mouse @ %f %f\n", event->motion.x, event->motion.y);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            scroll_vertical = event->wheel.y;
            scroll_horizontal = event->wheel.x;
            //printf("%f %f\n", event->wheel.x, event->wheel.y);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mouse_buttons[event->button.button] = true;
            //printf("click\n");
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouse_buttons[event->button.button] = false;
            //printf("release\n");
            break;
    }
}

bool InputState::key_down(SDL_Scancode sc) const
{
    return keys[sc];
}

bool InputState::key_pressed(SDL_Scancode sc) const
{
    return keys[sc] && !keys_previous[sc];
}

bool InputState::key_released(SDL_Scancode sc) const
{
    return keys_previous[sc] && !keys[sc];
}

bool InputState::mouse_down(SDL_MouseButtonFlags button) const
{
    return mouse_buttons[button];
}
bool InputState::mouse_pressed(SDL_MouseButtonFlags button) const
{
    return mouse_buttons[button] && !mouse_buttons_previous[button];
}
bool InputState::mouse_released(SDL_MouseButtonFlags button) const
{
    return mouse_buttons_previous[button] && !mouse_buttons[button];
}
