/*
 * main.c
 */

#include "segmentation.h"


void	main(void)
{
    init_flat_gdt();
    interrupts_init();
    irq_init(32);

	printk("Hello, world!");
	return;
}
