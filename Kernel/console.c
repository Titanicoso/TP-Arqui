#include <console.h>
#include <lib.h>

typedef struct {
	char ch;
	char style;
} cell_t;


typedef cell_t video_row[80];
static video_row *video = (video_row*) 0xB8000;


static const uint8_t width = 80;
static const uint8_t height = 25;
static const uint8_t cellSize = 2;              

static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static char defaultStyle = 0x07;

static char buffer[64];

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

void printc(char ch) {
	printcWithStyle(ch, defaultStyle);
}

void printcWithStyle(char ch, char style) {
	switch(ch) {
		case 8:
			backspace();
			break;
		case 10:
			newLine();
			break;
		default:
			video[cursorY][cursorX].ch = ch;
			video[cursorY][cursorX].style = style;
			incrementCursor();
			break;
	}
}

void print(char *s) {
	int i = 0;
	while(s[i] != 0) {
		printc(s[i]);
		i++;
	}
}

void println(char *s) {
	print(s);
	newLine();
}

void setStyle(char style) {
	defaultStyle = style;
}

void incrementCursor() {
	if(cursorX == width-1) {
		cursorX = 0;

		if(cursorY == height-1)
			shiftScreen();
		else
			cursorY++;
	}
	else
		cursorX++;
}

void newLine() {
	cursorX = 0;

	if(cursorY == height-1)
		shiftScreen();
	else
		cursorY++;
}

void backspace() {
	if(cursorY > 0 || cursorX > 0) {
		video[cursorY][cursorX].ch = ' ';
		if(cursorX == 0) {
			cursorX = width-1;
			cursorY--;
		}
		else
			cursorX--;
	}
}

void cursorUp() {
	if(cursorY > 0)
		cursorY--;
}

void cursorDown() {
	if(cursorY < height-1)
		cursorY++;
}

void cursorLeft() {
	if(cursorX > 0)
		cursorX--;
}

void cursorRight() {
	if(cursorX < width-1)
		cursorX++;
}

void blinkCursor() {
	video[cursorY][cursorX].style = 0x77 ^ video[cursorY][cursorX].style;
}

void shiftScreen() {
	memcpy((uint8_t*) video[0], (uint8_t*) video[1], cellSize*width*(height-1));
	for(uint8_t x = 0; x < width; x++) {
			video[height-1][x].ch = ' ';
			video[height-1][x].style = defaultStyle;
	}
}

void clearScreen() {
	for(uint8_t y = 0; y < height; y++) {
		for(uint8_t x = 0; x < width; x++) {
			video[y][x].ch = ' ';
			video[y][x].style = defaultStyle;
		}
	}
	cursorX = 0;
	cursorY = 0;
}

void printBase(uint64_t value, uint32_t base) {
	uintToBase(value, buffer, base);
	print(buffer);
}

void printDec(uint64_t value) {
	printBase(value, 10);
}

void printHex(uint64_t value) {
	printBase(value, 16);
}

void printBin(uint64_t value) {
	printBase(value, 2);
}

//From naiveConsole.c
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

