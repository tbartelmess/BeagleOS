all: derp.kernel

# Sources

SOURCES_ASM := boot.asm
SOURCES_C   := $(wildcard src/*.c)

PREFIX ?= /usr
CC      = $(PREFIX)/bin/arm-none-eabi-gcc
AS      = $(PREFIX)/bin/arm-none-eabi-as
LD      = $(PREFIX)/bin/arm-none-eabi-ld
OBJCOPY = $(PREFIX)/bin/arm-none-eabi-objcopy

CFLAGS += -march=armv7-a -mtune=cortex-a8 -Og

CFLAGS += --freestanding -msoft-float -fwrapv -fno-short-enums
CFLAGS += -std=gnu99 -fomit-frame-pointer -c -Isrc -I. -Iinclude
CFLAGS += -Wall -Wextra -Wshadow -Wcast-align -Wredundant-decls
CFLAGS += -Wno-div-by-zero -Wno-multichar -Wpadded
CFLAGS += -Wswitch-enum -Wdisabled-optimization

LDFLAGS += -init main -T linker.ld -N -Map kernel.map

# object files

#OBJS := $(patsubst %.asm,%.o,$(SOURCES_ASM))
OBJS += $(patsubst %.c,%.o,$(SOURCES_C))

derp.kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c Makefile
	$(CC) -S $(CFLAGS) $< -o $(<:.c=.s)
	$(AS) $(ASFLAGS) $(<:.c=.s) -o $@

%.o: %.asm Makefile
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean

clean:
	-rm -f derp.kernel
	-rm -f *.o
	-rm -f src/*.o
