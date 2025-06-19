#include "controller.h"
#include <SDL3/SDL.h>


controller::controller() {
	controller1.up = false;
	controller1.down = false;
	controller1.left = false;
	controller1.right = false;
	controller1.a = false;
	controller1.b = false;
	controller1.select = false;
	controller1.start = false;
	controller2.up = false;
	controller2.down = false;
	controller2.left = false;
	controller2.right = false;
	controller2.a = false;
	controller2.b = false;
	controller2.select = false;
	controller2.start = false;
}

Uint8 controller::getController1State() {
	Uint8 state = 0;
	if (controller1.a) state |= 0x01;
	if (controller1.b) state |= 0x02;
	if (controller1.select) state |= 0x04;
	if (controller1.start) state |= 0x08;
	if (controller1.up) state |= 0x10;
	if (controller1.down) state |= 0x20;
	if (controller1.left) state |= 0x40;
	if (controller1.right) state |= 0x80;
	return state;
}

Uint8 controller::getController2State() {
	Uint8 state = 0;
	if (controller2.a) state |= 0x01;
	if (controller2.b) state |= 0x02;
	if (controller2.select) state |= 0x04;
	if (controller2.start) state |= 0x08;
	if (controller2.up) state |= 0x10;
	if (controller2.down) state |= 0x20;
	if (controller2.left) state |= 0x40;
	if (controller2.right) state |= 0x80;
	return state;
}

void controller::handleEvent(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
		bool pressed = (event->type == SDL_EVENT_KEY_DOWN);
		switch (event->key.scancode) {
		case SDL_SCANCODE_UP: controller1.up = pressed; break;
		case SDL_SCANCODE_DOWN: controller1.down = pressed; break;
		case SDL_SCANCODE_LEFT: controller1.left = pressed; break;
		case SDL_SCANCODE_RIGHT: controller1.right = pressed; break;
		case SDL_SCANCODE_K: controller1.a = pressed; break;
		case SDL_SCANCODE_L: controller1.b = pressed; break;
		case SDL_SCANCODE_O: controller1.select = pressed; break;
		case SDL_SCANCODE_P: controller1.start = pressed; break;

		case SDL_SCANCODE_W: controller1.up = pressed; break;
		case SDL_SCANCODE_S: controller1.down = pressed; break;
		case SDL_SCANCODE_A: controller1.left = pressed; break;
		case SDL_SCANCODE_D: controller1.right = pressed; break;
		case SDL_SCANCODE_H: controller1.a = pressed; break;
		case SDL_SCANCODE_G: controller1.b = pressed; break;
		case SDL_SCANCODE_T: controller1.select = pressed; break;
		case SDL_SCANCODE_Y: controller1.start = pressed; break;
		}
	}
}