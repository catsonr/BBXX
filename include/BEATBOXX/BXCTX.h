#ifndef BXCTX_H
#define BXCTX_H

#include <BBXX/AudioState.h>
#include <BBXX/FileSystemState.h>
#include <BBXX/InputState.h>

struct BXCTX
{
    /* CONSTRUCTORS */

    BXCTX() = delete;
    BXCTX(
        AudioState& audiostate,
        FileSystemState& filesystemstate,
        InputState& inputstate
    ) :
        audiostate(audiostate),
        filesystemstate(filesystemstate),
        inputstate(inputstate)
    {}
    
    /* PUBLIC MEMBERS */
    const InputState& inputstate;
    FileSystemState& filesystemstate;
    AudioState& audiostate;

}; // BXCTX

#endif // BXCTX_H