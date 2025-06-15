#pragma once
#include <SDL3/SDL.h>
#include "vector"

class console;

struct pixelDetails {
	Uint8 source; // 0 = empty, 1 = back sprite, 2 = bg, 3 = front sprite
	Uint16 patternID;
	Uint8 paletteID;
	Uint8 colourID;
	Uint8 x;
	Uint8 y;
	Uint8 spriteID;
	bool hFlip;
	bool vFlip;
};

class ppu
{
public:
	console* myConsole;
	Uint8 nametable[1024];
	Uint8 paletteRAM[32];
	pixelDetails screenPixels[256 * 240][10]; // 256x240 pixels * 10 possible pixels per location
	Uint8 screenPixelsCnt[256 * 240];

	ppu();
	void render();
	
	Uint8 readReg(Uint16 address);
	void writeReg(Uint16 address, Uint8 v);
private:
	Uint8 ioBus;
	bool wReg;
	Uint8 palette[32]; 

	//reg 2000 PPUCTRL
	Uint16 baseNametableAddress;
	Uint8 vramAddressIncrement;
	Uint16 spritePatternTablee;
	Uint16 bgPatternTable;
	Uint8 spriteHeight;
	bool vblankNMIEnabled;
	void writeReg2000();

	//reg 2001 PPUMASK
	bool greyscale;
	bool showLeftmostBg;
	bool showLeftmostSprite;
	bool bgRenderingEnable;
	bool spriteRenderingEnable;
	bool emphasizeRed;
	bool emphasizeGreen;
	bool emphasizeBlue;
	void writeReg2001();

	//reg 2002 PPUSTATUS
	bool spriteOverflow;
	bool sprite0Hit;
	bool vblank;
	void readReg2002();

	//reg 2003 OAMADDR
	Uint8 oamAddr;
	void writeReg2003();

	//reg 2004 OAMDATA
	Uint8 oam[256];
	void readReg2004();
	void writeReg2004();

	//reg 2005 PPUSCROLL
	Uint8 scrollX;
	Uint8 scrollY;
	void writeReg2005();

	//reg 2006 PPUADDR
	Uint16 vramAddress;
	void writeReg2006();

	//reg 2007 PPUDATA
	void readReg2007();
	void writeReg2007();

	//reg 4014 OAMDMA
	void writeReg4014(Uint8 v);


};

