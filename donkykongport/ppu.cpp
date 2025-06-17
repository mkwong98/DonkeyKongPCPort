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
		bg0ColourIDs[i] = 0xFF;
		bgScreenPixels[i].colourID = 0xFF;
	}

	Uint16 pixelID = 0;
	spScreenPixelsCnt = 0;
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
		Uint16 patternValue2 = myConsole->rom.mapper->readPPU(patternSliceAddress + 8) << 1;

		Uint8 bg0ColourID = paletteRAM[0];
		if (greyscale) {
			bg0ColourID &= 0x30; // greyscale
		}

		Uint8 visibleSprites[8];
		Uint8 visibleSpritesCnt = 0;
		Uint8 visibleSpritePattern1[8];
		Uint16 visibleSpritePattern2[8];
		Uint8 visibleSpriteLine[8];
		for (Uint8 k = 0; k < 8; k++) {
			visibleSprites[k] = 0xFF; // no sprite
		}
		for (Uint8 k = 0; k < 64; k++) {
			Uint16 spriteY = oam[k * 4] + 1;
			if (j >= spriteY && j < spriteY + spriteHeight) {
				if (visibleSpritesCnt < 8) {
					visibleSpritesCnt++;
					visibleSprites[visibleSpritesCnt - 1] = k;
					Uint8 visibleLine = j - spriteY;
					if (oam[k * 4 + 2] & 0x80) { // vertical flip
						visibleLine = spriteHeight - 1 - visibleLine;
					}
					Uint16 patternTileAddress;
					if (spriteHeight == 8) {
						patternTileAddress = spritePatternTablee + (oam[k * 4 + 1] << 4) + visibleLine;
					}
					else{
						patternTileAddress = (oam[k * 4 + 1] & 0xFE) << 4;
						if (oam[k * 4 + 1] & 0x01) {
							patternTileAddress += 0x1000; // odd tile
						}
						if (visibleLine >= 8) {
							patternTileAddress += 16;
							visibleLine -= 8; // second half of the sprite
						}
						patternTileAddress += visibleLine;
					}
					visibleSpritePattern1[visibleSpritesCnt - 1] = myConsole->rom.mapper->readPPU(patternTileAddress);
					visibleSpritePattern2[visibleSpritesCnt - 1] = myConsole->rom.mapper->readPPU(patternTileAddress + 8) << 1;
				}
				else {
					spriteOverflow = true; // more than 8 sprites on the scanline
				}
			}
		}


		Uint8 paletteID = 0;
		for (Uint16 i = 0; i < 256; i++) {
			bg0ColourIDs[pixelID] = bg0ColourID;

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
						patternValue2 = myConsole->rom.mapper->readPPU(patternSliceAddress + 8) << 1;
					}
					Uint8 pixelValue = ((patternValue1 >> (7 - (viewX % 8))) & 0x01) | ((patternValue2 >> (7 - (viewX % 8))) & 0x02);
					bgPixelDetails bgPixel;
					bgPixel.patternID = patternTileAddress;
					bgPixel.paletteID = attributeID;
					if (pixelValue != 0) {
						bgPixel.colourID = paletteRAM[(attributeID << 2) + pixelValue];
						if (greyscale) {
							bgPixel.colourID &= 0x30; // greyscale
						}
					}
					else {
						bgPixel.colourID = 0xFF;
					}
					bgPixel.x = viewX % 8;
					bgPixel.y = viewY % 8;
					bgScreenPixels[pixelID] = bgPixel;
				}
			}

			if (spriteRenderingEnable) {
				if (i >= 8 or showLeftmostSprite) {
					bool spriteFound = false;
					for (int k = 0; k < visibleSpritesCnt; k++) {
						Uint8 spriteID = visibleSprites[k];
						if (oam[spriteID * 4 + 3] <= i && oam[spriteID * 4 + 3] + 8 > i) {
							spPixelDetails spPixel;
							spPixel.spriteID = spriteID;
							spPixel.patternID = oam[spriteID * 4 + 1];
							spPixel.paletteID = (oam[spriteID * 4 + 2] & 0x03);
							spPixel.front = !(oam[spriteID * 4 + 2] & 0x20);
							spPixel.hFlip = oam[spriteID * 4 + 2] & 0x40;
							spPixel.vFlip = oam[spriteID * 4 + 2] & 0x80;
							spPixel.visibleLine = visibleSpriteLine[k];
							
							Uint8 visiblePixel = i - oam[spriteID * 4 + 3];
							if (spPixel.hFlip) { 
								visiblePixel = 7 - visiblePixel;
							}
							spPixel.x = visiblePixel;

							Uint8 pixelValue = ((visibleSpritePattern1[k] >> (7 - visiblePixel)) & 0x01) | ((visibleSpritePattern2[k] >> (7 - visiblePixel)) & 0x02);
							if (pixelValue == 0) {
								spPixel.colourID = 0xFF; // transparent pixel
							}
							else {
								spPixel.colourID = paletteRAM[16 + ((oam[spriteID * 4 + 2] & 0x03) << 2) + pixelValue];
								if (greyscale) {
									spPixel.colourID &= 0x30; // greyscale
								}
							}

							if(!spriteFound){
								spPixelLocation[spScreenPixelsCnt].x = i;
								spPixelLocation[spScreenPixelsCnt].y = j;
								spPixelLocation[spScreenPixelsCnt].cnt = 0;
								spScreenPixelsCnt++;
								spriteFound = true;
							}
							spScreenPixels[spScreenPixelsCnt - 1][spPixelLocation[spScreenPixelsCnt - 1].cnt] = spPixel;
							spPixelLocation[spScreenPixelsCnt - 1].cnt++;
						}
					}
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
	spriteHeight = (ioBus & 0x20 ? 16 : 8);
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
		oam[i] = myConsole->rom.mapper->readCPU(pageAddress + i);
	}
}
