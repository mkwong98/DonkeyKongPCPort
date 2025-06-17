#include "ioPort.h"
#include "console.h"

ioPort::ioPort() {
	latch4016 = 0;
	d0_4016 = 0;
	d0_4017 = 0;
}

Uint8 ioPort::readReg(Uint16 address) {
	switch (address) {
	case 0x4016:
		return readReg4016();
		break;
	case 0x4017:
		return readReg4017();
		break;
	}
}

void ioPort::writeReg(Uint16 address, Uint8 v) {
	switch (address) {
	case 0x4016:
		writeReg4016(v);
		break;
	}
}

Uint8 ioPort::readReg4016() {
	if (latch4016 & 0x01) {
		d0_4016 = myConsole->controllers.getController1State();
	}
	Uint8 result = d0_4016 & 0x01;
	if (!(latch4016 & 0x01)) {
		d0_4016 >>= 1; // shift the bits to the right 1;
	}
	return result;
}

void ioPort::writeReg4016(Uint8 v) {
	if (latch4016 & 0x01) {
		d0_4016 = myConsole->controllers.getController1State();
		d0_4017 = myConsole->controllers.getController1State();
	}
	latch4016 = v;
}

Uint8 ioPort::readReg4017() {
	if (latch4016 & 0x01) {
		d0_4017 = myConsole->controllers.getController1State();
	}
	Uint8 result = d0_4017 & 0x01;
	if (!(latch4016 & 0x01)) {
		d0_4017 >>= 1; // shift the bits to the right 1;
	}
	return result;
}
