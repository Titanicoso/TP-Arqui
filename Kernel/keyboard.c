#include <keyboard.h>
#include <lib.h>

static uint8_t buffer[256];
static uint8_t shift = 0;
static uint8_t mayus = 0;

void keyboardHandler() {
	uint8_t input = readPort(0x60);
	parseScanCode(input);
}

void parseScanCode(uint8_t scanCode) {
	printHex(scanCode);
}