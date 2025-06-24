#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>

using namespace std;

class console;

struct inputSetting {
	Uint8 type; //0=none, 1=keyboard, 2=joystick axis, 3=joystick hat, 4=joystick button
	Uint32 v;
};

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

	vector<SDL_Joystick*>js;
	inputSetting inputSettings[2][8];

	controller();
	~controller();
	Uint8 getController1State();
	Uint8 getController2State();
	void init();
	void handleEvent(SDL_Event* event);
	void setConfig(string h, string t);
};

