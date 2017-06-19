#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>

void sysRead(uint64_t fileDescriptor, uint64_t buffer, uint64_t size);

void sysWrite(uint64_t fileDescriptor, uint64_t buffer, uint64_t size);

void sysSetTimeZone(uint64_t timeZone, uint64_t rdx, uint64_t rcx);

void sysGetTime(uint64_t hour, uint64_t minute, uint64_t seconds);

void sysGetDate(uint64_t day, uint64_t month, uint64_t year);

void sysEcho(uint64_t echoOn, uint64_t rdx, uint64_t rcx);

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

void sysCallsSetup();

#endif
