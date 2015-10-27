/*
 * serial.c
 */

#define PORT 0x3f8   /* COM1 */

void init_serial()
{
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x80);
	outb(PORT + 0, 0x03);
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x03);
	outb(PORT + 2, 0x00);
	outb(PORT + 4, 0x00);
}

int is_transmit_empty()
{
	return inb(PORT + 5) & 0x20;
}

void serial_putchar(char c)
{
	while (is_transmit_empty() == 0);

	outb(PORT, c);
}

void serial_putstr(const char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] != '\0') {
		serial_putchar(str[i++]);
	}
}
