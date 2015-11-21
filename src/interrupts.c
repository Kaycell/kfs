#include "interrupts.h"
#include "memset.h"

/*
 * IDT entry
 * 64 bits struct
 * Packed to avoid compiler optimization
 */
struct idt_entry
{
    unsigned short base_low;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

typedef int (*isr_handler)(struct regs *regs);

void interrupts_set_isr(int n, isr_handler handler, unsigned char flags)
{
    idt[n].base_low = ((unsigned int)handler & 0xFFFF);
    idt[n].base_high = ((unsigned int)handler >> 16) & 0xFFFF;

    idt[n].sel = 0x08;
    idt[n].zero = 0;
    idt[n].flags = flags;
}

extern void interrupts_load();
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void interrupts_init(void)
{
    idtp.limit = (sizeof(struct regs) * 256) - 1;
    idtp.base = (unsigned int)&idt;

    memset(&idt, 0, sizeof(struct regs) * 256);

    /*
     * Set 32 first ISR
     */
    interrupts_set_isr(0, (isr_handler)_isr0, 0x8E);
    interrupts_set_isr(1, (isr_handler)_isr1, 0x8E);
    interrupts_set_isr(2, (isr_handler)_isr2, 0x8E);
    interrupts_set_isr(3, (isr_handler)_isr3, 0x8E);
    interrupts_set_isr(4, (isr_handler)_isr4, 0x8E);
    interrupts_set_isr(5, (isr_handler)_isr5, 0x8E);
    interrupts_set_isr(6, (isr_handler)_isr6, 0x8E);
    interrupts_set_isr(7, (isr_handler)_isr7, 0x8E);
    interrupts_set_isr(8, (isr_handler)_isr8, 0x8E);
    interrupts_set_isr(9, (isr_handler)_isr9, 0x8E);
    interrupts_set_isr(10, (isr_handler)_isr10, 0x8E);
    interrupts_set_isr(11, (isr_handler)_isr11, 0x8E);
    interrupts_set_isr(12, (isr_handler)_isr12, 0x8E);
    interrupts_set_isr(13, (isr_handler)_isr13, 0x8E);
    interrupts_set_isr(14, (isr_handler)_isr14, 0x8E);
    interrupts_set_isr(15, (isr_handler)_isr15, 0x8E);
    interrupts_set_isr(16, (isr_handler)_isr16, 0x8E);
    interrupts_set_isr(17, (isr_handler)_isr17, 0x8E);
    interrupts_set_isr(18, (isr_handler)_isr18, 0x8E);
    interrupts_set_isr(19, (isr_handler)_isr19, 0x8E);
    interrupts_set_isr(20, (isr_handler)_isr20, 0x8E);
    interrupts_set_isr(21, (isr_handler)_isr21, 0x8E);
    interrupts_set_isr(22, (isr_handler)_isr22, 0x8E);
    interrupts_set_isr(23, (isr_handler)_isr23, 0x8E);
    interrupts_set_isr(24, (isr_handler)_isr24, 0x8E);
    interrupts_set_isr(25, (isr_handler)_isr25, 0x8E);
    interrupts_set_isr(26, (isr_handler)_isr26, 0x8E);
    interrupts_set_isr(27, (isr_handler)_isr27, 0x8E);
    interrupts_set_isr(28, (isr_handler)_isr28, 0x8E);
    interrupts_set_isr(29, (isr_handler)_isr29, 0x8E);
    interrupts_set_isr(30, (isr_handler)_isr30, 0x8E);
    interrupts_set_isr(31, (isr_handler)_isr31, 0x8E);

    interrupts_load();
}

/*
 * ISR messages
 */
const char* exception_messages[] = 
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern void _page_fault(struct regs* r);

/*
 * Exception handler
 */
void _fault_handler(struct regs r)
{
    if (r.int_no < 32)
    {
        printk("\n");
        printk(exception_messages[r.int_no]);
        printk(" Exception.\nSystem Halted!\n\0");
        for (;;);
    }
}
