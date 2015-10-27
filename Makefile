TARGET	= kfs

NASM	= nasm

NFLAGS	= -f elf32

CFLAGS	+= -nostdinc -fno-builtin -m32
CFLAGS	+= -fno-stack-protector

LDFLAGS	+= -T kfs.ld -nostdlib -m32 -Wl,--build-id=none

SRCDIR	= src

SRC	= $(SRCDIR)/main.c

ASM	= $(SRCDIR)/crt0.S

OBJS	= $(SRC:.c=.o) $(ASM:.S=.o)

QEMU	= qemu-system-x86_64

GDB	= gdb

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(NASM) $(NFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all

boot:	$(TARGET)
	$(QEMU) -kernel $(TARGET)

debug:	$(TARGET)
	$(QEMU) -s -S -daemonize -kernel $(TARGET)	
	$(GDB) $(TARGET) -ex "target remote localhost:1234"
