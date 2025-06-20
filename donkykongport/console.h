#pragma once
#include "game.h"
#include "ppu.h"
#include "apu.h"
#include "ioPort.h"
#include "rom.h"

#include "render.h"
#include "sound.h"
#include "controller.h"

const Uint64 FRAME_DURATION_NS = 16666667; // 1/60 seconds in nanoseconds
const Uint64 FRAME_COUNTER_NS = 4166667; // 1/240 seconds in nanoseconds


class console
{
public:
	game cpu;
	ppu ppu;
	apu apu;
	rom rom;
	ioPort iop;

	render renderer;
	sound snd;
	controller controllers;



	console();
	void runFrame();
	void readConfig();
};

