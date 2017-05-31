#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void iSetHandler(int index, uint64_t handler);
void sti();
void cli();
void setPicMaster(uint8_t mask);
void setPicSlave(uint8_t mask);
void sendEOI(int irq);
void setupIDT();
void irqDispatcher(int irq);
void tickHandler();

extern void irq0Handler();
extern void irq1Handler();
extern void irq12Handler();

#endif
