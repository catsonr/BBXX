#include <BBXX/AudioState.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <stdio.h>

bool AudioState::init()
{
    ma_result result;
    result = ma_engine_init(NULL, &engine);
    if( result != MA_SUCCESS ) {
        printf("[AudioState::init] failed to initialize miniaudio!\n");
        return false;
    }

    return true;
}

void AudioState::iterate()
{

}