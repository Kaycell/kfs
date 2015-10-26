void	printk(const char *msg)
{
	char *video_ptr = (char*)0xb8000;
	unsigned int i = 0;
	unsigned int j = 0;

	while(msg[j] != '\0') {
		video_ptr[i] = msg[j];
		video_ptr[i + 1] = 0x07;
		++j;
		i = i + 2;	
	}
}

void	main(void)
{
	printk("Hello, World!");
	return;
}
