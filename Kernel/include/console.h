#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

#define WIDTH 80
#define HEIGHT 25

void printc(char ch);

void printcWithStyle(char ch, char style);

void print(char *s);

void println(char *s);

void printBase(uint64_t val, uint32_t base);

void setStyle(char style);

void incrementCursor();

void newLine();

void backspace();

void cursorUp();

void cursorDown();

void cursorLeft();

void cursorRight();

void blinkCursor();

void shiftScreen();

void clearScreen();

void printBase(uint64_t value, uint32_t base);

void printDec(uint64_t value);

void printHex(uint64_t value);

void printBin(uint64_t value);

#endif