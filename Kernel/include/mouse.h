#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <stdint.h>

uint8_t mouse_read();
void mouse_write(uint8_t a_write);
void initializeMouse();
void mouseHandler();

#endif