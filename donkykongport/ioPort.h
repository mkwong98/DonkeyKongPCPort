#pragma once
#include <SDL3/SDL.h>

class console;

class ioPort
{
public:
	console* myConsole;

	ioPort();
	Uint8 readReg(Uint16 address);
	void writeReg(Uint16 address, Uint8 v);

private:
	Uint8 latch4016;
	Uint8 d0_4016;
	Uint8 d0_4017;
	Uint8 readReg4016();
	void writeReg4016(Uint8 v);
	Uint8 readReg4017();

};

