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
EXTERN runModule

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

	cmp rdi, 7
	jne .end
	cmp rax, 0
	jne .end
	mov QWORD[rsp], runModule
.end:
	iretq

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
