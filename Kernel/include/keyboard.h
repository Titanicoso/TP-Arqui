#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

void keyboardHandler();
void parseScanCode(uint8_t scanCode);

#endif