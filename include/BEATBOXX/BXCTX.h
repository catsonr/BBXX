#ifndef BXCTX_H
#define BXCTX_H

#include <BBXX/InputState.h>

struct BXCTX
{
    /* CONSTRUCTORS */

    BXCTX() = delete;
    BXCTX(InputState& inputstate) :
        inputstate(inputstate)
    {}
    
    /* PUBLIC MEMBERS */
    const InputState& inputstate;
}; // BXCTX

#endif // BXCTX_H