#include "game.h"
#include "console.h"
#include "mapper.h"

game::game() {
	a = 0;
	x = 0;
	y = 0;
	s = 0;
	flgC = false;
	flgZ = false;
	flgI = true;
	flgD = false;
	flgV = false;
	flgN = false;
	flgB = false;
}

Uint8 game::getStatus() {
	Uint8 p = 0x20;
	if (flgC) p |= 0x01;
	if (flgZ) p |= 0x02;
	if (flgI) p |= 0x04;
	if (flgD) p |= 0x08;
	if (flgB) p |= 0x10;
	if (flgV) p |= 0x40;
	if (flgN) p |= 0x80;
	return p;
}

void game::setStatus(Uint8 p) {
	flgC = p & 0x01;
	flgZ = p & 0x02;
	flgI = p & 0x04;
	flgD = p & 0x08;
	flgB = p & 0x10;
	flgV = p & 0x40;
	flgN = p & 0x80;
}

void game::opADC(Uint8 v) {
	Uint16 result = a + v + (flgC ? 1 : 0);
	flgC = result > 0xff;
	flgZ = result == 0;
	flgV = (result ^ a) & (result ^ v) & 0x80;
	flgN = result & 0x80;
	a = result & 0xff;	
}

void game::opSBC(Uint8 v) {
	opADC(~v);
}

void game::opAND(Uint8 v) {
	a &= v;
	flgZ = a == 0;
	flgN = a & 0x80;
}

void game::opORA(Uint8 v) {
	a |= v;
	flgZ = a == 0;
	flgN = a & 0x80;
}

void game::opEOR(Uint8 v) {
	a ^= v;
	flgZ = a == 0;
	flgN = a & 0x80;
}

void game::opBIT(Uint8 v) {
	Uint8 result = a & v;
	flgZ = a == 0;
	flgV = v & 0x40;
	flgN = v & 0x80;
}

void game::opINC(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = (myMapper->readCPU(address) + repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result);
}

void game::opDEC(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = (myMapper->readCPU(address) + 0x0100 - repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result);
}

void game::opINX(Uint8 repeatTimes) {
	Uint16 result = (x + repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	x = result;
}

void game::opDEX(Uint8 repeatTimes) {
	Uint16 result = (x + 0x0100 - repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	x = result;
}

void game::opINY(Uint8 repeatTimes) {
	Uint16 result = (y + repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	y = result;
}

void game::opDEY(Uint8 repeatTimes) {
	Uint16 result = (y + 0x0100 - repeatTimes) & 0x00ff;
	flgZ = result == 0;
	flgN = result & 0x80;
	y = result;
}

void game::opASL_A(Uint8 repeatTimes) {
	Uint16 result = a << repeatTimes;
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	a = result & 0x00ff;
}

void game::opASL_M(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = myMapper->readCPU(address) << repeatTimes;
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result & 0x00ff);
}

void game::opLSR_A(Uint8 repeatTimes) {
	Uint16 result = a >> repeatTimes;
	flgC = (a >> (repeatTimes -1)) & 0x01;
	flgZ = result == 0;
	flgN = result & 0x80;
	a = result & 0x00ff;
}

void game::opLSR_M(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = myMapper->readCPU(address) >> repeatTimes;
	flgC = (myMapper->readCPU(address) >> (repeatTimes - 1)) & 0x01;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result & 0x00ff);
}

void game::opROL_A(Uint8 repeatTimes) {
	Uint16 result = a | (flgC ? 0x0100 : 0); // Include carry bit in the result
	result = (result << repeatTimes) | (result >> (9 - repeatTimes));
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	a = result & 0x00ff;
}

void game::opROL_M(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = myMapper->readCPU(address) | (flgC ? 0x0100 : 0); // Include carry bit in the result
	result = (result << repeatTimes) | (result >> (9 - repeatTimes));
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result & 0x00ff);
}

void game::opROR_A(Uint8 repeatTimes) {
	Uint16 result = a | (flgC ? 0x0100 : 0); // Include carry bit in the result
	result = (result >> repeatTimes) | (result << (9 - repeatTimes));
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	a = result & 0x00ff;
}

void game::opROR_M(Uint16 address, Uint8 repeatTimes) {
	Uint16 result = myMapper->readCPU(address) | (flgC ? 0x0100 : 0); // Include carry bit in the result
	result = (result >> repeatTimes) | (result << (9 - repeatTimes));
	flgC = result & 0x0100;
	flgZ = result == 0;
	flgN = result & 0x80;
	myMapper->writeCPU(address, result & 0x00ff);
}

void game::pushAddress(Uint16 address) {
	mStack.push({ true, address });
	mStack.push({ true, address });
}

void game::popAddress() {
	poppedEntry = mStack.top();
	mStack.pop();
	mStack.pop();
}

void game::pushStatus() {
	mStack.push({ false, getStatus() });
}

void game::popStatus() {
	setStatus(mStack.top().value);
	mStack.pop();
}

void game::opPLA() {
	a = mStack.top().value;
	mStack.pop();
	flgZ = a == 0;
	flgN = a & 0x80;
}

void game::setLoadFlag(Uint8 v) {
	flgZ = v == 0;
	flgN = v & 0x80;
}

void game::opCMP(Uint8 v1, Uint8 v2) {
	flgC = v1 >= v2;
	flgZ = v1 == v2;
	Uint16 result = (v1 < v2 ? v1 + 0x100 - v2 : v1 - v2);
	flgN = result & 0x80;
}
