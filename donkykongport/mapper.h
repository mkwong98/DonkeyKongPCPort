#pragma once
#include <SDL3/SDL.h>

class rom;

class mapper
{
public:
	rom* rom;
	Uint8 ram[0x800];

	virtual void init() = 0;
	virtual Uint8 readCPU(Uint16 address) = 0;
	virtual void writeCPU(Uint16 address, Uint8 value) = 0;
	virtual Uint8 readPPU(Uint16 address) = 0;
	virtual void writePPU(Uint16 address, Uint8 value) = 0;
};

