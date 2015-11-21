#include "segmentation.h"

/*
 * GDT entry
 * Packed to avoid compiler optimization
 */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low; 
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/*
 * GDT pointer
 * Also packed
 */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/*
 * GDT with 3 entries
 *  0 -> NULL segment
 *  1 -> Code segment
 *  2 -> Data segment
 */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_reload();

int set_gdt_entry(int n, unsigned int base, unsigned int limit, unsigned char access, unsigned char granularity)
{
    /*
     * Setup base address
     */
    gdt[n].base_low = (base & 0xFFFF);
    gdt[n].base_middle = (base >> 16) & 0xFF;
    gdt[n].base_high = (base >> 24) & 0xFF;

    /*
     * Setup limits
     */
    gdt[n].limit_low = (limit & 0xFFFF);
    gdt[n].granularity = ((limit >> 16) & 0x0F);

    /*
     * set up the granularity and access flags
     */
    gdt[n].granularity |= (granularity & 0xF0);
    gdt[n].access = access;

    return n;
}

void init_flat_gdt(void)
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int)&gdt;

    /*
     * NULL descriptor
     */
    set_gdt_entry(0, 0, 0, 0, 0);

    /*
     * Code Segment
     * The base address is 0
     * the limit is 4GBytes
     * it uses 4KByte granularity,
     * uses 32-bit opcodes
     * and is a Code Segment descriptor.
     */
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /*
     * Data Segment
     * same as our code segment
     * the descriptor type says it's a Data Segment
     */
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /*
     * Reload GDT
     */
    gdt_reload();
}
