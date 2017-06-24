GLOBAL sti
GLOBAL cli
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL irq12Handler
GLOBAL PFHandler
GLOBAL setPicMaster
GLOBAL setPicSlave
GLOBAL int80Handler
GLOBAL int80

%include "./asm/macros.m"

EXTERN irqDispatcher
EXTERN sysCallHandler
EXTERN sendEOI
EXTERN pageFaultHandler

section .text

irq0Handler:
	irqHandler 0

irq1Handler:
	irqHandler 1

irq12Handler:
	irqHandler 12

PFHandler:
	mov DWORD[rbp+8], pageFaultHandler
	iretq

int80Handler:
	pushaq

	call sysCallHandler

	popaq

	iretq

int80: ; Int 80 No va aca, es solo para probar.
	pushaq
	int 80h
	popaq
	ret

sti:
	sti
	ret

cli:
	cli
	ret

setPicMaster:
	setPicMask 0x21

setPicSlave:
	setPicMask 0xA1
