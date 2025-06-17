#pragma once
#include <SDL3/SDL.h>

class console;

struct buttons{
	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool select;
	bool start;
};

class controller
{
public:
	console* myConsole;

	buttons controller1;
	buttons controller2;

	controller();
	Uint8 getController1State();
	Uint8 getController2State();
	void handleEvent(SDL_Event* event);
};

