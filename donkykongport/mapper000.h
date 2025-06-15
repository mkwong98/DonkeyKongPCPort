#pragma once
#include <SDL3/SDL.h>
#include "mapper.h"

class mapper000: public mapper
{
public:
	void init();
	Uint8 readCPU(Uint16 address);
	void writeCPU(Uint16 address, Uint8 value);
	Uint8 readPPU(Uint16 address);
	void writePPU(Uint16 address, Uint8 value);
};

