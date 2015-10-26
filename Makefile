TARGET	= kfs

CFLAGS	+= -nostdinc -fno-builtin -m32
CFLAGS	+= -fno-stack-protector

LDFLAGS	+= -T kfs.ld -nostdlib -m32 -Wl,--build-id=none

SRCDIR	= src

SRC	= $(SRCDIR)/main.c

ASM	= $(SRCDIR)/crt0.S

OBJS	= $(SRC:.c=.o) $(ASM:.S=.o)

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(TARGET)

boot:

debug:
