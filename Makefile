all: derp.kernel

# Sources

SOURCES_ASM := boot.asm

PREFIX ?= /usr
CC      = $(PREFIX)/bin/arm-none-eabi-gcc
AS      = $(PREFIX)/bin/arm-none-eabi-as
LD      = $(PREFIX)/bin/arm-none-eabi-ld
OBJCOPY = $(PREFIX)/bin/arm-none-eabi-objcopy

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
