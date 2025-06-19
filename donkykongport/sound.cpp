#include "sound.h"
#include "console.h"

void SDLCALL sound::FeedAudioStream(void* userdata, SDL_AudioStream* astream, int additional_amount, int total_amount)
{
    sound* snd = static_cast<sound*>(userdata);
    snd->fillBuffer(astream, additional_amount, total_amount);
}

sound::sound() {
    pulse1Cycle = 0;
    pulse2Cycle = 0;
    triangleCycle = 0;
}

void sound::fillBuffer(SDL_AudioStream* astream, int additional_amount, int total_amount) {
    additional_amount /= sizeof(float);  /* convert from bytes to samples */
    while (additional_amount > 0) {
        float samples[128];  /* this will feed 128 samples each iteration until we have enough. */
        float pulse1Samples[128];
        float pulse2Samples[128];
        float triangleSamples[128];

        const int total = SDL_min(additional_amount, SDL_arraysize(samples));

        genPulseWave(myConsole->apu.pulse1Settings, pulse1Samples, total, &pulse1Cycle);
        genPulseWave(myConsole->apu.pulse2Settings, pulse2Samples, total, &pulse2Cycle);
        genTriangleWave(triangleSamples, total);

        for (int i = 0; i < total; i++) {
            samples[i] = 0.2256 * (pulse1Samples[i] + pulse2Samples[i]) +(0.2553 * triangleSamples[i]);
        }

        /* feed the new data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
        SDL_PutAudioStreamData(astream, samples, total * sizeof(float));
        additional_amount -= total;  /* subtract what we've just fed the stream. */
    }
}


void sound::genPulseWave(pulseSettings p, float* output, int samples, float* cycle) {
    if (p.lengthCounter > 0 && p.timer >= 8 && p.targetPeriod < 0x800) {
        float cyclePerSample = (1789773.0 / (4 * (p.timer + 1))) / 48000.0;
        float vol = (p.outputVolume / 7.5) - 1.0;
        for (int i = 0; i < samples; i++) {
            (*cycle) += cyclePerSample;
            if ((*cycle) > 4.0) (*cycle) -= 4.0;
            if (pulseDuty[p.dutyCycle][(int)*cycle]) {
                output[i] = vol;
            }
            else {
                output[i] = -1;
            }
        }
    }
    else {
        for (int i = 0; i < samples; i++) {
            output[i] = -1;
        }
    }
}

void sound::genTriangleWave(float* output, int samples) {
    if (myConsole->apu.triangleLengthCounter > 0 && myConsole->apu.triangleLinearCounter) {
        float cyclePerSample = (1789773.0 / (32 * (myConsole->apu.triangleTimer + 1))) / 48000.0;
        for (int i = 0; i < samples; i++) {
            triangleCycle += cyclePerSample;
            if (triangleCycle > 1.0) triangleCycle -= 1.0;
            float vol;
            if (triangleCycle < 0.5) {
                output[i] = -1 + triangleCycle * 4;
            }
            else{
                output[i] = 1 - ((triangleCycle - 0.5) * 4);
            }
        }
    }
    else {
        for (int i = 0; i < samples; i++) {
            output[i] = -1;
        }
    }
}

