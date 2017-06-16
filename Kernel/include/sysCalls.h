#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>

void sysRead(uint64_t fileDescriptor, uint64_t buffer, uint64_t size);

void sysWrite(uint64_t fileDescriptor, uint64_t buffer, uint64_t size);

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

void sysCallsSetup();

#endif
