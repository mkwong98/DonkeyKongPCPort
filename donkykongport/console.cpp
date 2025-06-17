#include "console.h"

console::console() {
	cpu.myConsole = this;
	ppu.myConsole = this;
	apu.myConsole = this;
	rom.myConsole = this;
	iop.myConsole = this;

	renderer.myConsole = this;
	controllers.myConsole = this;
}

void console::runFrame(Uint64 ns) {
	cpu.nmi();
	ppu.render();
	renderer.renderFrame();
}