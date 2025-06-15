#pragma once
#include <SDL3/SDL.h>

class console;

class render
{
public:
	console* myConsole;
	SDL_Renderer* renderer;

	void renderFrame();
	void loadPalette(SDL_IOStream* palFile);

private:
	SDL_Color colors[64];

};

