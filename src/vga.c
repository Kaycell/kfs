/*
 * vga.c
 */

enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
static const unsigned int VGA_WIDTH = 80;
static const unsigned int VGA_HEIGHT = 25;
static unsigned short* VGA_TERMINAL_BUFFER = (void*)0xB8000;
 
unsigned int vga_terminal_row;
unsigned int vga_terminal_column;
unsigned char vga_terminal_color;

unsigned char get_full_vga_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
unsigned short get_vgachar(char c, unsigned char color) {
	unsigned short c16 = c;
	unsigned short color16 = color;
	return c16 | color16 << 8;
}
 
void init_vga_terminal() {
	unsigned int y;
	unsigned int x;

	vga_terminal_row = 0;
	vga_terminal_column = 0;
	vga_terminal_color = get_full_vga_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	y = 0;
	while (y < VGA_HEIGHT) {
		x = 0;
		while (x < VGA_WIDTH) {
			const unsigned int index = y * VGA_WIDTH + x;
			VGA_TERMINAL_BUFFER[index] = get_vgachar(' ', vga_terminal_color);
			++x;
		}
		++y;
	}
}
 
void vga_terminal_setcolor(unsigned char color) {
	vga_terminal_color = color;
}
 
void vga_terminal_putcharat(char c, unsigned char color, unsigned int x, unsigned int y) {
	unsigned int coord_1d;

	coord_1d = y * VGA_WIDTH + x;
	VGA_TERMINAL_BUFFER[coord_1d] = get_vgachar(c, color);
}
 
void vga_terminal_putchar(char c) {
	if (c == '\n') {
		vga_terminal_column = 0;
		if (++vga_terminal_row == VGA_HEIGHT) {
			vga_terminal_row = 0;
		}
	return;
	}

	vga_terminal_putcharat(c, vga_terminal_color, vga_terminal_column, vga_terminal_row);
	if (++vga_terminal_column == VGA_WIDTH) {
		vga_terminal_column = 0;
		if (++vga_terminal_row == VGA_HEIGHT) {
			vga_terminal_row = 0;
		}
	}
}
 
void vga_terminal_putstr(const char* str) {
	unsigned int i;

	i = 0;
	while (str[i] != '\0')
		vga_terminal_putchar(str[i++]);
}
