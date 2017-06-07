#include <keyboard.h>
#include <console.h>
#include <lib.h>
#include <scanCodes.h>

#define BUFFER_SIZE (WIDTH*HEIGHT)+1000

static uint8_t buffer[BUFFER_SIZE];
static uint8_t writeIndex = 0;
static uint8_t readIndex = 0;
static uint8_t shiftMayus = 0;
static uint8_t leftShift = FALSE;
static uint8_t rightShift = FALSE;
static uint8_t specialKey = FALSE;
//static uint8_t mayus = 0;

void keyboardHandler() {
	uint8_t input = readPort(0x60);
	parseScanCode(input);
}

void parseScanCode(uint8_t scanCode) {
	if(specialKey)
		parseSpecialKey(scanCode);
	else {
		switch(scanCode) {
			case LEFT_SHIFT_PRESS:
			case LEFT_SHIFT_RELEASE:
			case RIGHT_SHIFT_PRESS:
			case RIGHT_SHIFT_RELEASE:
			case CAPSLOCK_PRESS:
			case CAPSLOCK_RELEASE:
			case BACKSPACE_PRESS:
			case ENTER_PRESS:
				parseSpecialKey(scanCode);
				break;

			case SPECIAL_KEY:
				specialKey = TRUE;
				break;

			default:
				if(scanCode < 0x80) {
					char ch = scanCodes[shiftMayus][scanCode];
					if(ch != 0) {
						printc(ch);
						writeBuffer(ch);
					}
				}
				break;
		}
	}
}

void parseSpecialKey(uint8_t scanCode) {
	specialKey = FALSE;

	switch(scanCode) {
		case LEFT_SHIFT_PRESS:
			leftShift = TRUE;
			shiftMayus = shiftMayus | SHIFT;
			break;
		case RIGHT_SHIFT_PRESS:
			rightShift = TRUE;
			shiftMayus = shiftMayus | SHIFT;
			break;

		case LEFT_SHIFT_RELEASE:
			leftShift = FALSE;
			if(!(leftShift || rightShift))
				shiftMayus =  shiftMayus & NOT_SHIFT;
			break;

		case RIGHT_SHIFT_RELEASE:
			rightShift = FALSE;
			if(!(leftShift || rightShift))
				shiftMayus =  shiftMayus & NOT_SHIFT;
			break;

		case CAPSLOCK_PRESS:
			shiftMayus = shiftMayus ^ MAYUS;
			break;

		/*case CAPSLOCK_RELEASE:
			shiftMayus = shiftMayus & NOT_MAYUS;
			printDec(shiftMayus);
			break;*/

		case BACKSPACE_PRESS:
			backspace();
			writeBuffer('\b');
			break;

		case ENTER_PRESS:
			newLine();
			writeBuffer('\n');
			break;

		case CURSOR_UP:
			cursorUp();
			break;

		case CURSOR_DOWN:
			cursorDown();
			break;

		case CURSOR_LEFT:
			cursorLeft();
			break;

		case CURSOR_RIGHT:
			cursorRight();
			break;

		default:
			break;
	}
}

void writeBuffer(char ch) {
	buffer[writeIndex] = ch;
	writeIndex++;
}

void writeStringToBuffer(char *s, uint16_t size) {

}

