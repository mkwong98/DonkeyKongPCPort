#pragma once
#include "game.h"
#include "ppu.h"
#include "apu.h"
#include "ioPort.h"
#include "rom.h"

#include "render.h"
#include "controller.h"

class console
{
public:
	game cpu;
	ppu ppu;
	apu apu;
	rom rom;
	ioPort iop;

	render renderer;
	controller controllers;

	console();
	void runFrame(Uint64 ns);
};

