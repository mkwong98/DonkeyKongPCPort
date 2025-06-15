#pragma once
#include <SDL3/SDL.h>

class mapper;
class console;

class rom
{
public:
	console* myConsole;
	Uint8* chrData;
	Uint8* prgData;
	mapper* mapper;

	void loadROM(SDL_IOStream* romFile);
	~rom();

	bool nametableArrangementH; //0 = vertical arrangement / horizontal mirrored
	bool hasPersistentMemory;
	bool hasTrainer;
	bool useAlternativeNametableLayout;
	Uint32 prgROMSize;
	Uint32 chrROMSize;
};

