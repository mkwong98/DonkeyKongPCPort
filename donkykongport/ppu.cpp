#include "ppu.h"
#include "binaryUtil.h"
#include "rom.h"
#include "console.h"
#include "mapper.h"

ppu::ppu() {
	writeReg(0x2000, 0);
	writeReg(0x2001, 0);
	vblank = true;
	spriteOverflow = false;
	sprite0Hit = false;
	oamAddr = 0;
	wReg = false;
	scrollX = 0;
	scrollY = 0;
	vramAddress = 0;
	ioBus = 0;
}


void ppu::render() {
	for (int i = 0; i < 256 * 240; i++) {
		screenPixelsCnt[i]=0; 
	}

	Uint16 pixelID = 0;
	for (Uint16 j = 0; j < 240; j++) {
		Uint16 viewY = scrollY + j;
		Uint8 attributeShiftY = ((viewY % 32) >= 16 ? 4 : 0);

		Uint16 nametableAddress = baseNametableAddress;
		Uint16 attributeTableAddress = baseNametableAddress + 0x3C0; 
		//check crossed nametable vertical boundary
		if (viewY >= 240) {
			nametableAddress ^= 0x800;
			attributeTableAddress ^= 0x800;
		}
		Uint16 nametableRowAddress = nametableAddress + (((viewY % 240) << 2) & 0xFFE0); //divide by 8 to get the row, multiply by 32 to get address of the row
		Uint16 nametableTileAddress = nametableRowAddress + (scrollX >> 3); //divide by 8 to get the column
		Uint8 nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

		Uint16 attributeTableRowAddress = attributeTableAddress + (((viewY % 240) >> 2) & 0xFFF8); //divide by 32 to get the row, multiply by 8 to get address of the row
		Uint16 attributeTableTileAddress = attributeTableRowAddress + (scrollX >> 5); //divide by 32 to get the column
		Uint8 attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);

		Uint16 viewX = scrollX;
		Uint8 attributeShiftX = ((viewX % 32) >= 16 ? 2 : 0);
		Uint8 attributeID = attributeTableValue >> (attributeShiftY + attributeShiftX) & 0x03;

		Uint16 patternTileAddress = bgPatternTable + (nametableValue << 4);
		Uint16 patternSliceAddress = patternTileAddress + (viewY % 8);
		Uint8 patternValue1 = myConsole->rom.mapper->readPPU(patternSliceAddress);
		Uint8 patternValue2 = myConsole->rom.mapper->readPPU(patternSliceAddress + 8);

		pixelDetails bg0Pixel;
		bg0Pixel.source = 0;
		bg0Pixel.colourID = paletteRAM[0];
		bg0Pixel.patternID = 0;
		bg0Pixel.paletteID = 0;
		bg0Pixel.x = 0;
		bg0Pixel.y = 0;
		bg0Pixel.spriteID = 0;
		bg0Pixel.hFlip = false;
		bg0Pixel.vFlip = false;
		if (greyscale) {
			bg0Pixel.colourID &= 0x30; // greyscale
		}

		Uint8 visibleSprites[8];
		Uint8 visibleSpritesCnt = 0;
		Uint8 visibleSpritePattern[8][2];
		for (Uint8 k = 0; k < 8; k++) {
			visibleSprites[k] = 0xFF; // no sprite
		}
		for (Uint8 k = 0; k < 64; k++) {
			Uint16 spriteY = oam[k * 4] + 1;
			if (j >= spriteY && j < spriteY + spriteHeight) {
				if (visibleSpritesCnt < 8) {
					visibleSprites[visibleSpritesCnt++] = k;
				}
				else {
					spriteOverflow = true; // more than 8 sprites on the scanline
				}
			}
		}


		Uint8 paletteID = 0;
		for (Uint16 i = 0; i < 256; i++) {
			screenPixels[pixelID][0] = bg0Pixel;
			screenPixelsCnt[i]++;

			if (bgRenderingEnable) {
				if (i >= 8 or showLeftmostBg) {
					if ((viewX % 8) == 0 && i > 0) {
						//move to next tile
						if (viewX == 256) {
							nametableRowAddress ^= 0x400;
							nametableTileAddress = nametableRowAddress;
							nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

							attributeTableRowAddress ^= 0x400;
							attributeTableTileAddress = attributeTableRowAddress;
							attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);
							attributeShiftX = 0;
						}
						else {
							nametableTileAddress++;
							nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

							if ((viewX % 32) == 0) {
								attributeTableTileAddress++;
							}
							if ((viewX % 16) == 0) {
								attributeShiftX ^= 2; // toggle attribute shift
							}
							attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);
						}
						attributeID = (attributeTableValue >> (attributeShiftY + attributeShiftX)) & 0x03;

						patternTileAddress = bgPatternTable + (nametableValue << 4);
						patternSliceAddress = patternTileAddress + (viewY % 8);
						patternValue1 = myConsole->rom.mapper->readPPU(patternSliceAddress);
						patternValue2 = myConsole->rom.mapper->readPPU(patternSliceAddress + 8);
					}
					Uint8 pixelValue = ((patternValue1 >> (7 - (viewX % 8))) & 0x01) | (((patternValue2 >> (7 - (viewX % 8))) & 0x01) << 1);
					pixelDetails bgPixel;
					bgPixel.source = 2; // Background
					bgPixel.patternID = patternTileAddress;
					bgPixel.paletteID = attributeID;
					if (pixelValue != 0) {
						bgPixel.colourID = paletteRAM[(attributeID << 2) + pixelValue];
						if (greyscale) {
							bg0Pixel.colourID &= 0x30; // greyscale
						}
					}
					else {
						bgPixel.colourID = 0xFF;
					}
					bgPixel.x = viewX % 8;
					bgPixel.y = viewY % 8;
					screenPixels[pixelID][1] = bgPixel;
					screenPixelsCnt[i]++;
				}
			}
			viewX++;
			pixelID++;
		}
	}
}

Uint8 ppu::readReg(Uint16 address) {
	switch (address) {
	case 0x2002:
		readReg2002();
		break;
	case 0x2004:
		readReg2004();
		break;
	case 0x2007:
		readReg2007();
		break;
	}
	return ioBus;
}

void ppu::writeReg(Uint16 address, Uint8 v) {
	ioBus = v;
	switch (address) {
	case 0x2000:
		writeReg2000();
		break;
	case 0x2001:
		writeReg2001();
		break;
	case 0x2003:
		writeReg2003();
		break;
	case 0x2004:
		writeReg2004();
		break;
	case 0x2005:
		writeReg2005();
		break;
	case 0x2006:
		writeReg2006();
		break;
	case 0x2007:
		writeReg2007();
		break;
	}
}


void ppu::writeReg2000() {
	switch (ioBus & 0x03) {
	case 0x00:
		baseNametableAddress = 0x2000;
		break;
	case 0x01:
		baseNametableAddress = 0x2400;
		break;
	case 0x02:
		baseNametableAddress = 0x2800;
		break;
	case 0x03:
		baseNametableAddress = 0x2C00;
		break;
	}
	vramAddressIncrement = (ioBus & 0x04 ? 32 : 1);
	spritePatternTablee = (ioBus & 0x08 ? 0x1000 : 0x0000);
	bgPatternTable = (ioBus & 0x10 ? 0x1000 : 0x0000);
	spriteHeight = (ioBus & 0x20 ? 8 : 16);
	vblankNMIEnabled = ioBus & 0x80;
}

void ppu::writeReg2001(){
	greyscale = ioBus & 0x01;
	showLeftmostBg = ioBus & 0x02;
	showLeftmostSprite = ioBus & 0x04;
	bgRenderingEnable = ioBus & 0x08;
	spriteRenderingEnable = ioBus & 0x10;
	emphasizeRed = ioBus & 0x20;
	emphasizeGreen = ioBus & 0x40;
	emphasizeBlue = ioBus & 0x80;
}

void ppu::readReg2002(){
	ioBus &= 0x1F;
	if (spriteOverflow) ioBus |= 0x20;
	if (sprite0Hit) ioBus |= 0x40;
	if (vblank) ioBus |= 0x80;
	vblank = false;
	wReg = false;
}

void ppu::writeReg2003(){
	oamAddr = ioBus;
}

void ppu::readReg2004(){
	ioBus = oam[oamAddr];
}

void ppu::writeReg2004(){
	oam[oamAddr] = ioBus;
	binaryUtil::inc(&oamAddr);
}

void ppu::writeReg2005(){
	if (!wReg) scrollX = ioBus;
	else scrollY = ioBus;
	wReg = !wReg;
}

void ppu::writeReg2006(){
	if (!wReg) vramAddress = (ioBus << 8) & 0x3F00;
	else vramAddress |= ioBus;
	wReg = !wReg;
}

void ppu::readReg2007(){
	ioBus = myConsole->rom.mapper->readPPU(vramAddress);
	vramAddress += vramAddressIncrement;
}

void ppu::writeReg2007(){
	myConsole->rom.mapper->writePPU(vramAddress, ioBus);
	vramAddress += vramAddressIncrement;
}

void ppu::writeReg4014(Uint8 v){
	Uint16 pageAddress = v << 8;
	for (Uint16 i = 0; i < 256; i++) {
		oam[i] = myConsole->rom.mapper->readCPU(v + i);
	}
}
