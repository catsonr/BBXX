#ifndef AUDIOSTATE_H
#define AUDIOSTATE_H

#include <BBXX/FileSystemState.h>

#include <miniaudio.h>

#include <vector>

#define INITIAL_VOLUME 1.0

struct AudioState
{
    /* PUBLIC MEMBERS */
    
    ma_engine engine;
    
    std::vector<ma_sound> sounds;

    /* PUBLIC METHODS */

    bool init(const FileSystemState& filesystemstate);
    void iterate();
    void cleanup();
}; // AudioState

#endif // AudioState