all: derp.kernel

# Sources

SOURCES_ASM := boot.asm

PREFIX ?= /usr
CC      = $(PREFIX)/bin/arm-linux-gnueabi-gcc
AS      = $(PREFIX)/bin/arm-linux-gnueabi-as
LD      = $(PREFIX)/bin/arm-linux-gnueabi-ld
OBJCOPY = $(PREFIX)/bin/arm-linux-gnueabi-objcopy

CFLAGS += --freestanding -msoft-float -fwrapv -fno-short-enums
CFLAGS += -std=gnu99 -fomit-frame-pointer -c -Isrc -I. -Iinclude
CFLAGS += -Wall -Wextra -Wshadow -Wcast-align -Wredundant-decls
CFLAGS += -Wno-div-by-zero -Wno-multichar -Wpadded
CFLAGS += -Wswitch-enum -Wdisabled-optimization

LDFLAGS += -T linker.ld

# object files

OBJS := $(patsubst %.asm,%.o,$(SOURCES_ASM))

derp.kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean
	-rm -f derp.kernel
	-rm -f *.o
