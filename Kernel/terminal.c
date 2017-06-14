#include <terminal.h>
#include <lib.h>
#include <video.h>


static video_row videoBuffer[25];

static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static uint8_t videoY = 0;
static char defaultStyle = 0x07;

static uint8_t mouseX = 0;
static uint8_t mouseY =0;

static char buffer[64];

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
			toggleCursors();
			printChar(ch, style);
			toggleCursors();
			break;
	}
}

void printChar(char ch, char style) {
	videoBuffer[cursorY][cursorX].style = style;
	videoBuffer[cursorY][cursorX].ch = ch;
	writeAtCursor(ch, style);
	incrementCursor();
}

void print(char *s) {
	toggleCursors();
	int i = 0;
	while(s[i] != 0) {
		printChar(s[i], defaultStyle);
		i++;
	}
	toggleCursors();
}

void println(char *s) {
	print(s);
	newLine();
}

void setStyle(char style) {
	defaultStyle = style;
}

void incrementCursor() {
	if(cursorX == WIDTH-1) {
		cursorX = 0;

		if(cursorY == HEIGHT-1)
			shiftScreen();
	}
	else
		cursorX++;
	
	updateCursor(cursorX, cursorY);
}

void newLine() {
	toggleCursors();
	cursorX = 0;

	if(cursorY == HEIGHT-1)
		shiftScreen();
	else
		cursorY++;
	updateCursor(cursorX, cursorY);
	toggleCursors();
}

void backspace() { //TODO anda para el ogt con enter
	if(cursorY > 0 || cursorX > 0) {
		toggleCursors();
		videoBuffer[cursorY][cursorX].ch = ' ';
		if(cursorX == 0) {
			cursorX = WIDTH-1;
			cursorY--;
		}
		else
			cursorX--;
		updateCursor(cursorX, cursorY);
		toggleCursors();
	}
}

void cursorUp() {
	if(cursorY > 0)
		cursorY--;
}

void cursorDown() {
	if(cursorY < HEIGHT-1)
		cursorY++;
}

void cursorLeft() {
	if(cursorX > 0)
		cursorX--;
}

void cursorRight() {
	if(cursorX < WIDTH-1)
		cursorX++;
}

void shiftScreen() {
	//memcpy((uint8_t*) video[0], (uint8_t*) video[1], CELLSIZE*WIDTH*(HEIGHT-1));
	for(uint8_t x = 0; x < WIDTH; x++) {
		videoBuffer[videoY+HEIGHT][x].ch = 0;
		videoBuffer[videoY+HEIGHT][x].style;
	}
	videoY++;
	updateScreen();
}

void clearScreen() {
	toggleCursors();
	cursorY++;
	for(uint8_t y = cursorY; y < cursorY+HEIGHT; y++) {
		for(uint8_t x = 0; x < WIDTH; x++) {
			videoBuffer[y][x].ch = ' ';
			videoBuffer[y][x].style = defaultStyle;
		}
	}
	cursorX = 0;
	cursorY = 0;
	updateCursor(0, 0);
	toggleCursors();
}

void updateScreen() {
	for(uint8_t y = videoY; y < videoY+HEIGHT; y++) {
		for(uint8_t x = 0; x < WIDTH; x++) {
				writeScreen(x, y-videoY, videoBuffer[y][x].ch, videoBuffer[y][x].style);
		}
	}
}

uint8_t getCharAt(uint8_t x, uint8_t y) {
    return videoBuffer[y][x].ch;
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



