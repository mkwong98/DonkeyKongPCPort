#include "render.h"
#include "console.h"

void render::renderFrame() {
	SDL_SetRenderTarget(renderer, internalScreen);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	Uint16 pixelID = 0;
	Uint16 spPixelID = 0;
	for (int j = 0; j < 240; j++) {
		for (int i = 0; i < 256; i++) {

			Uint8 pixel;

			bool hasSP = false;
			bool spIsFront = false;
			Uint8 spColourID;
			if (spPixelID < myConsole->ppu.spScreenPixelsCnt) {
				if (myConsole->ppu.spPixelLocation[spPixelID].y == j && myConsole->ppu.spPixelLocation[spPixelID].x == i) {
					Uint8 spID = 0;
					while (spID < myConsole->ppu.spPixelLocation[spPixelID].cnt && !hasSP) {
						if (myConsole->ppu.spScreenPixels[spPixelID][spID].colourID != 0xFF) {
							hasSP = true;
							spIsFront = myConsole->ppu.spScreenPixels[spPixelID][spID].front;
							spColourID = myConsole->ppu.spScreenPixels[spPixelID][spID].colourID;
						}
						else {
							spID++;
						}
					}
					spPixelID++;
				}
			}
			if (hasSP && spIsFront) {
				// render sprite pixel
				pixel = spColourID;
			}
			else if (myConsole->ppu.bgScreenPixels[pixelID].colourID != 0xFF) {
				// render background pixel
				pixel = myConsole->ppu.bgScreenPixels[pixelID].colourID;
			}
			else if (hasSP) {
				pixel = spColourID;
			}
			else {
				pixel = myConsole->ppu.bg0ColourIDs[pixelID];
			}
			if (pixel != 0xFF) {
				SDL_SetRenderDrawColor(renderer, colors[pixel].r, colors[pixel].g, colors[pixel].b, SDL_ALPHA_OPAQUE);
				SDL_RenderPoint(renderer, i, j);
			}
			pixelID++;
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderTexture(renderer, internalScreen, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void render::loadPalette(SDL_IOStream* palFile) {
	Uint8 pal[192];
	SDL_ReadIO(palFile, pal, 192);
	for (int i = 0; i < 64; i++) {
		colors[i].r = pal[i * 3];
		colors[i].g = pal[i * 3 + 1];
		colors[i].b = pal[i * 3 + 2];
		colors[i].a = SDL_ALPHA_OPAQUE;
	}
	SDL_CloseIO(palFile);
}

void render::setConfig(string h, string t) {
	if (h == "PALETTE") {
		loadPalette(SDL_IOFromFile(t.c_str(), "rb"));
	}
	else if (h == "WIDTH") {
		displayWidth = std::stoi(t);
	}
	else if (h == "HEIGHT") {
		displayHeight = std::stoi(t);
	}
}

render::render() {
	displayWidth = 256;
	displayHeight = 240;
}


void render::init(SDL_Renderer* r) {
	renderer = r;
	internalScreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 256, 240);
}

void render::cleanUp() {
	if (internalScreen) SDL_DestroyTexture(internalScreen);
}