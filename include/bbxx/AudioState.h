#ifndef AUDIOSTATE_H
#define AUDIOSTATE_H

#include <miniaudio.h>

struct AudioState
{
    /* PUBLIC MEMBERS */
    
    ma_engine engine;

    /* PUBLIC METHODS */

    bool init();
    void iterate();
}; // AudioState

#endif // AudioState