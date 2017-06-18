#include <terminal.h>
#include <lib.h>
#include <video.h>


static video_row videoBuffer[HEIGHT];

static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static char defaultStyle = 0x07;

static uint8_t mouseX = 0;
static uint8_t mouseY = 0;

static char buffer[64];

void updateScreen();

void printChar(char ch, char style) {
	videoBuffer[cursorY][cursorX].style = style;
	videoBuffer[cursorY][cursorX].ch = ch;
	writeAtCursor(ch, style);
	incrementCursor();
}

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
	while (cursorX < WIDTH) {
		videoBuffer[cursorY][cursorX].ch = 0;
		cursorX++;
	}
	cursorX = 0;

	if(cursorY == HEIGHT-1)
		shiftScreen();
	else
		cursorY++;
	updateCursor(cursorX, cursorY);
	updateScreen();
	toggleCursors();
}

void backspace() {
	if(cursorY > 0 || cursorX > 0) {
		toggleCursors();
		int x = cursorX;
		int y = cursorY;
		int prevX;
		int prevY;
		if(x == 0) {
			prevX = WIDTH-1;
			prevY = y-1;
		}
		else {
			prevX = x-1;
			prevY = y;
		}
		int offset = 0;
		cursorX = prevX;
		cursorY = prevY;
		while(prevY >= 0 && videoBuffer[prevY][prevX].ch == 0) {
			offset++;
			cursorX = prevX;
			cursorY = prevY;
			prevX--;
			if(prevX < 0) {
				prevX = WIDTH-1;
				prevY--;
			}
		}
		if(offset == 0)
			offset = 1;

		do {
			prevX = x - offset;
			prevY = y;
			while (prevX < 0) {
				prevX += WIDTH;
				prevY--;
			}

			videoBuffer[prevY][prevX] = videoBuffer[y][x];
			videoBuffer[y][x].ch = 0;

			if(x == WIDTH-1) {
				x = 0;
				y++;
			}
			else
				x++;

		} while(y < HEIGHT && videoBuffer[prevY][prevX].ch != 0);

		updateCursor(cursorX, cursorY);
		updateScreen();
		toggleCursors();
	}
}

void cursorUp() {
	toggleCursors();
	if(cursorY > 0)
		cursorY--;
	while (cursorX > 0 && videoBuffer[cursorY][cursorX].ch == 0)
		cursorX--;
	updateCursor(cursorX, cursorY);
	toggleCursors();
}

void cursorDown() {
	toggleCursors();
	if(cursorY < HEIGHT-1)
		cursorY++;
	while (cursorX > 0 && videoBuffer[cursorY][cursorX].ch == 0)
		cursorX--;
	updateCursor(cursorX, cursorY);
	toggleCursors();
}

void cursorLeft() {
	toggleCursors();
	if(cursorX > 0)
		cursorX--;
	else if(cursorY > 0) {
		cursorY--;
		while(cursorX < WIDTH-1 && videoBuffer[cursorY][cursorX].ch != 0)
			cursorX++;
	}
	updateCursor(cursorX, cursorY);
	toggleCursors();
}

void cursorRight() {
	toggleCursors();
	if(cursorX == WIDTH-1 || videoBuffer[cursorY][cursorX].ch == 0) {
		if(cursorY < HEIGHT-1) {
			cursorY++;
			cursorX = 0;
		}
	}
	else
		cursorX++;
	updateCursor(cursorX, cursorY);
	toggleCursors();
}

void updateScreen() {
	for(uint8_t y = 0; y < HEIGHT; y++) {
		for(uint8_t x = 0; x < WIDTH; x++) {
				writeScreen(x, y, videoBuffer[y][x].ch, videoBuffer[y][x].style);
		}
	}
}

void shiftScreen() {
	memcpy((uint8_t*) videoBuffer[0], (uint8_t*) videoBuffer[1], CELLSIZE*WIDTH*(HEIGHT-1));
	for(uint8_t x = 0; x < WIDTH; x++) {
		videoBuffer[HEIGHT-1][x].ch = 0;
		videoBuffer[HEIGHT-1][x].style = defaultStyle;
	}
	updateScreen();
}

void clearScreen() {
	toggleCursors();
	for(uint8_t y = 0; y < HEIGHT; y++) {
		for(uint8_t x = 0; x < WIDTH; x++) {
			videoBuffer[y][x].ch = 0;
			videoBuffer[y][x].style = defaultStyle;
		}
	}
	cursorX = 0;
	cursorY = 0;
	updateCursor(0, 0);
	updateScreen();
	toggleCursors();
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
