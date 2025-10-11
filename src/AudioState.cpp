#include <BBXX/AudioState.h>

#define MINIAUDIO_IMPLEMENTATION
//#define MA_ENABLE_AUDIO_WORKLETS
#include <miniaudio.h>

#include <stdio.h>

bool AudioState::init(const FileSystemState& filesystemstate)
{
    if( ma_engine_init(NULL, &engine) != MA_SUCCESS ) {
        printf("[AudioState::init] failed to initialize miniaudio!\n");
        return false;
    }
    
    ma_engine_set_volume(&engine, INITIAL_VOLUME);
    
    return true;
}

void AudioState::iterate()
{

}

void AudioState::cleanup()
{
    for( ma_sound& sound : sounds )
        ma_sound_uninit(&sound);

    ma_engine_uninit(&engine);
}