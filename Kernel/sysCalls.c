#include <sysCalls.h>
#include <terminal.h>
#include <naiveConsole.h>

#define SYSCALLS 10

typedef void (*sys)(uint64_t rsi, uint64_t rdx, uint64_t rcx);

static sys sysCalls[SYSCALLS];

void sysRead(uint64_t fileDescriptor, uint64_t buffer, uint64_t size) {
	if(fileDescriptor == 0) {
		/*ReadFromBuffer()*/;
	}
}

void sysWrite(uint64_t fileDescriptor, uint64_t buffer, uint64_t size) {
	if(fileDescriptor == 1 || fileDescriptor == 2) {
		char next;
		while(size--) {
			next = *(char *)(buffer++);
			if(fileDescriptor == 1)
				printc(next);
			else 
				printcWithStyle(next, 0x04);
		}
	}
}

void sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx) {
	clearScreen();
}

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
	if(rdi < 0 || rdi >= SYSCALLS)
		return; //Tirar error??
	sysCalls[rdi](rsi, rdx, rcx);
}

void sysCallsSetup(){
	sysCalls[0] = &sysRead;
	sysCalls[1] = &sysWrite;
	sysCalls[2] = &sysClear;
}