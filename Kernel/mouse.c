#include <mouse.h>

uint8_t mouse_read() {
	return readPort(0x60);
}

void mouse_write(uint8_t a_write) {
	writePort(0x64, 0xD4);
	writePort(0x60, a_write);
}

void initializeMouse() {
	writePort(0x64,0xA8);
	writePort(0x64,0x20);
	uint8_t status_byte;
	status_byte = (readPort(0x60) | 2);
	writePort(0x64, 0x60);
	writePort(0x60, status_byte);
	mouse_read();
	mouse_write(0xF4);
	mouse_read();
}

void mouseHandler() {
	static uint8_t mouse_bytes[3];
	static uint8_t cycle = 0;

	mouse_bytes[cycle++] = readPort(0x60);

	if(cycle == 3) {
		cycle = 0;
		println("Hola");
	}
}

/*void mouseHandler()
{
  static unsigned char cycle = 0;
  static char mouse_bytes[3];
  mouse_bytes[cycle++] = readPort(0x60);
 
  if (cycle == 3) { // if we have all the 3 bytes...
    cycle = 0; // reset the counter
    // do what you wish with the bytes, this is just a sample
    if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
      return; // the mouse only sends information about overflowing, do not care about it and return
    if (mouse_bytes[0] & 0x4)
      println("Middle button is pressed!");
    if (mouse_bytes[0] & 0x2)
      println("Right button is pressed!");
    if (mouse_bytes[0] & 0x1)
      println("Left button is pressed!");
    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  }
}*/

