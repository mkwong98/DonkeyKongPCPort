#include "render.h"
#include "console.h"

void render::renderFrame() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for (int i = 0; i < 256 * 240; i++) {
		Uint8 pixel;
		if (myConsole->ppu.screenPixels[i][1].colourID == 0xFF) {
			pixel = myConsole->ppu.screenPixels[i][0].colourID;
		}
		else {
			pixel = myConsole->ppu.screenPixels[i][1].colourID;
		}
		SDL_SetRenderDrawColor(renderer, colors[pixel].r, colors[pixel].g, colors[pixel].b, SDL_ALPHA_OPAQUE);
		SDL_RenderPoint(renderer, i % 256, i / 256);
	}
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