/*
 * printk.c
 */

static char vga_is_init = 0;
static char serial_is_init = 0;

void printk(const char *msg)
{
	if (!vga_is_init) {
		init_vga_terminal();
		++vga_is_init;
	}
	if (!serial_is_init) {
		init_serial();
		++serial_is_init;
	}

	vga_terminal_putstr(msg);
	serial_putstr(msg);
}

