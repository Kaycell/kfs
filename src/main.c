/*
 * main.c
 */

#include "segmentation.h"


void	main(void)
{
    init_flat_gdt();
    interrupts_init();

	printk("Hello, world!");
	return;
}
