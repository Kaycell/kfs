;;crt0.S

bits 32
section .multiboot
	align		4
	dd		0x1BADB002
	dd		0x00
	dd		-(0x1BADB002 + 0x00)

global _start
global inb
global outb
extern main

_start:
	push ebx	;multiboot info
	push eax	;magic
	call main	;kernel entry point
	hlt		;halt cpu

inb:
	mov edx, [esp + 4]
	in al, dx	
	ret

outb:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret
