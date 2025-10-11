#ifndef AUDIOSCREEN_H
#define AUDIOSCREEN_H

#include <BEATBOXX/ScreenState/Screen.h>
#include <BBXX/AudioState.h>

struct AudioScreen : public Screen
{
    AudioScreen(const char* name, BXCTX& bxctx) :
    Screen(name, bxctx),
    audiostate(bxctx.audiostate)
    {}

    AudioState& audiostate;

    bool init() override
    {
        audiostate.sounds.emplace_back();
        ma_sound& sound = audiostate.sounds.back();
        ma_uint32 flags =
            MA_SOUND_FLAG_NO_SPATIALIZATION |
            MA_SOUND_FLAG_ASYNC
        ;

        if( ma_sound_init_from_file(&audiostate.engine, bxctx.filesystemstate.get_path("sounds/Galaxy.mp3").c_str(), flags, NULL, NULL, &sound) != MA_SUCCESS ) {
            printf("[AudioState::init] failed to init Galaxy.mp3 as a sound!\n");
            return false;
        }

        //ma_sound_start(&sound);
        
        return true;
    }
}; // AudioSCreen

#endif // AUDIOSCREN_H