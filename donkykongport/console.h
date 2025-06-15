#pragma once
#include "game.h"
#include "ppu.h"
#include "apu.h"
#include "rom.h"
#include "render.h"

class console
{
public:
	game cpu;
	ppu ppu;
	apu apu;
	rom rom;
	render renderer;

	console();
	void runFrame(Uint64 ns);
};

