#pragma once
#include <SDL3/SDL.h>

struct pulseSettings;
class console;

class sound
{
public:
    static void SDLCALL FeedAudioStream(void* userdata, SDL_AudioStream* astream, int additional_amount, int total_amount);
    const Uint8 pulseDuty[4][8] = {{ 0, 1, 0, 0, 0, 0, 0, 0 }, 
                                   { 0, 1, 1, 0, 0, 0, 0, 0 }, 
                                   { 0, 1, 1, 1, 1, 0, 0, 0 }, 
                                   { 1, 0, 0, 1, 1, 1, 1, 1 }};

    console* myConsole;
    
    sound();
    float pulse1Cycle;
    float pulse2Cycle;
    float triangleCycle;
    void fillBuffer(SDL_AudioStream* astream, int additional_amount, int total_amount);
    void genPulseWave(pulseSettings p, float* output, int samples, float* cycle);
    void genTriangleWave(float* output, int samples);

};
