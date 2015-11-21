#include "irq.h"

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15(); 

void irq_remap()
{

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

int irq_init(unsigned char base)
{
    /*
     * Init PIC
     */
    irq_remap();

    interrupts_set_isr(base + 0, (isr_handler)_irq0, 0x8E);
    interrupts_set_isr(base + 1, (isr_handler)_irq1, 0x8E);
    interrupts_set_isr(base + 2, (isr_handler)_irq2, 0x8E);
    interrupts_set_isr(base + 3, (isr_handler)_irq3, 0x8E);
    interrupts_set_isr(base + 4, (isr_handler)_irq4, 0x8E);
    interrupts_set_isr(base + 5, (isr_handler)_irq5, 0x8E);
    interrupts_set_isr(base + 6, (isr_handler)_irq6, 0x8E);
    interrupts_set_isr(base + 7, (isr_handler)_irq7, 0x8E);
    interrupts_set_isr(base + 8, (isr_handler)_irq8, 0x8E);
    interrupts_set_isr(base + 9, (isr_handler)_irq9, 0x8E);
    interrupts_set_isr(base + 10, (isr_handler)_irq10, 0x8E);
    interrupts_set_isr(base + 11, (isr_handler)_irq11, 0x8E);
    interrupts_set_isr(base + 12, (isr_handler)_irq12, 0x8E);
    interrupts_set_isr(base + 13, (isr_handler)_irq13, 0x8E);
    interrupts_set_isr(base + 14, (isr_handler)_irq14, 0x8E);
    interrupts_set_isr(base + 15, (isr_handler)_irq15, 0x8E);
}

void irq_send_eoi(void)
{
    outb(0x20, 0x20);
}
