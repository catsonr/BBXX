#include <BBXX/AudioState.h>

#define MINIAUDIO_IMPLEMENTATION
//#define MA_ENABLE_AUDIO_WORKLETS
#include <miniaudio.h>

#include <stdio.h>

bool AudioState::init(const FileSystemState& filesystemstate)
{
    ma_result result;
    result = ma_engine_init(NULL, &engine);
    if( result != MA_SUCCESS ) {
        printf("[AudioState::init] failed to initialize miniaudio!\n");
        return false;
    }
    
    sounds.emplace_back();
    ma_sound& sound = sounds.back();

    result = ma_sound_init_from_file(&engine, filesystemstate.get_path("sounds/Galaxy.mp3").c_str(), 0, NULL, NULL, &sound);
    if( result != MA_SUCCESS ) {
        printf("[AudioState::init] failed to init Galaxy.mp3 as a sound!\n");
        return false;
    }
    
    ma_sound_start(&sound);

    return true;
}

void AudioState::iterate()
{

}

void AudioState::cleanup()
{
    // ma_sound_uninit()

    ma_engine_uninit(&engine);
}