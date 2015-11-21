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
global gdt_reload
global interrupts_load
extern idtp
extern gp
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

gdt_reload:
    lgdt [gp]
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment
flush2:
    ret

interrupts_load:
    lidt [idtp]
    ret
