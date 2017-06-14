#include <video.h>
#include <terminal.h>


static video_row *video = (video_row*) 0xB8000;
static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static uint8_t cursorVisible = FALSE;
static uint8_t fromX = 0;
static uint8_t fromY = 0;
static uint8_t toX = 0;
static uint8_t toY = 0;


void writeScreen(uint8_t x, uint8_t y, char ch, char style) {
	toggleCursors();
	if(ch == 0)
		video[y][x].ch = ' ';
	else
		video[y][x].ch = ch;
	
	video[y][x].style = style;
	toggleCursors();
}

void writeAtCursor(char ch, char style) {
	if(ch == 0)
		video[cursorY][cursorX].ch = ' ';
	else
		video[cursorY][cursorX].ch = ch;
	
	video[cursorY][cursorX].style = style;
}

void toggleCursors() {
	if(cursorVisible)
		video[cursorY][cursorX].style = 0x77 ^ video[cursorY][cursorX].style;

	uint8_t xOff = toX - fromX;
	uint8_t yOff = toY - fromY;
	uint8_t xStep = (xOff > 0)? 1 : -1;
	uint8_t yStep = (yOff > 0)? 1 : -1;
	do {
		do {
			video[fromY+yOff][fromX+xOff].style = 0x77 ^ video[fromY+yOff][fromX+xOff].style;

		}while(xOff != 0);
	}while(yOff != 0);
}

void updateCursor(uint8_t x, uint8_t y) {
	toggleCursors();
	cursorX = x;
	cursorY = y;
	toggleCursors();
}

void updateMouse(uint8_t x, uint8_t y) {
	toggleCursors();
	fromX = toX = x;
	fromY = toY = y;
	toggleCursors();
}

void selectTo(uint8_t x, uint8_t y) {
	toggleCursors();
	toX = x;
	toY = y;
	toggleCursors();
}

void blinkCursor() {
	if(cursorVisible)
		cursorVisible = FALSE;
	else
		cursorVisible = TRUE;
}