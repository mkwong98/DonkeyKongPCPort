
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "console.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window * window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_AudioStream* stream = NULL;

static console myConsole;
static Uint64 time = 0;
static Uint64 apuTime = 0;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("Donky Kong Port", "0.0", "donkykongport.mkwong98");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("", 256, 240, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    myConsole.rom.loadROM(SDL_IOFromFile("..\\x64\\Debug\\Donkey Kong (JU).nes", "rb"));
	myConsole.renderer.loadPalette(SDL_IOFromFile("..\\x64\\Debug\\2C02G_wiki.pal", "rb"));
	myConsole.renderer.renderer = renderer;

    SDL_AudioSpec spec;
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = 48000;
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, sound::FeedAudioStream, &(myConsole.snd));
    if (!stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

	/* Reset the CPU to start the program. */
	myConsole.cpu.reset();
    SDL_ResumeAudioStreamDevice(stream);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
	if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
		myConsole.controllers.handleEvent(event);
	}
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    myConsole.cpu.repeat();
    Uint64 newTime = SDL_GetTicksNS();
    Uint64 timeDif = newTime - time;
    if (timeDif >= FRAME_DURATION_NS) {
        myConsole.runFrame();
        time = newTime;
    }

    Uint64 apuTimeDif = newTime - apuTime;
    if (apuTimeDif >= FRAME_COUNTER_NS) {
        myConsole.apu.runFrame();
        apuTime = newTime;
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}