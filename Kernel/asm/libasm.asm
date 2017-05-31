GLOBAL cpuVendor
GLOBAL sti
GLOBAL cli
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL setPicMaster
GLOBAL setPicSlave
GLOBAL input
GLOBAL output

EXTERN irqDispatcher

%include "./asm/macros.m"

section .text

irq0Handler:
	irqHandler 0

irq1Handler:
	irqHandler 1

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

input:	;(Recibe el puerto a leer en rdi)
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	in al, dx

	mov rsp, rbp
	pop rbp
	ret

output: ;(Recibe el puerto a escribir en rdi y en rsi lo que hay que escribir)
	push rbp
	mov rbp, rsp

	mov rax, rsi
	mov rdx, rdi
	out dx, al

	mov rsp, rbp
	pop rbp
	ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
