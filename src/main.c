/*
 * main.c
 */

#include "segmentation.h"


void	main(void)
{
    init_flat_gdt();

	printk("Hello, world!");
	return;
}
