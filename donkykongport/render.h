#pragma once
#include <SDL3/SDL.h>
#include "string"

using namespace std;

class console;

class render
{
public:
	console* myConsole;
	SDL_Renderer* renderer;
	SDL_Texture* internalScreen;

	int displayWidth;
	int displayHeight;

	render();
	void init(SDL_Renderer* r);
	void cleanUp();
	void setConfig(string h, string t);
	void renderFrame();

private:
	SDL_Color colors[64];
	void loadPalette(SDL_IOStream* palFile);

};

