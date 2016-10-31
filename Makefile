all: beagleOS.bin

# Sources

SOURCES_ASM := $(wildcard src/*.asm)
SOURCES_C   := $(wildcard src/*.c)

PREFIX  = /usr
CC      = $(PREFIX)/bin/arm-none-eabi-gcc
AS      = $(PREFIX)/bin/arm-none-eabi-as
LD      = $(PREFIX)/bin/arm-none-eabi-ld
OBJCOPY = $(PREFIX)/bin/arm-none-eabi-objcopy

ASFLAGS += -mapcs-32 -march=armv7-a

CFLAGS  += -march=armv7-a -mtune=cortex-a8 -Og

CFLAGS  += -ffreestanding -fwrapv -fno-short-enums
CFLAGS  += -std=gnu11 -c -Isrc -I.
CFLAGS  += -Wall -Wextra -Wshadow -Wcast-align -Wredundant-decls
CFLAGS  += -Wdiv-by-zero -Wno-multichar -Wpadded
CFLAGS  += -Wswitch-enum -Wdisabled-optimization
CFLAGS += -D __BUILD_NUM__=$(shell cat VERSION)

LDFLAGS += -T linker.ld -Map kernel.map -N --warn-unresolved-symbols

# object files

OBJS := $(patsubst %.asm,%.o,$(SOURCES_ASM))
OBJS += $(patsubst %.c,%.o,$(SOURCES_C))

beagleOS.bin: beagleOS.elf
	$(OBJCOPY) --target elf32-littlearm --set-section-flags .bss=contents,alloc,load -O binary $< $@

beagleOS.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c Makefile
	$(CC) -S $(CFLAGS) $< -o $(<:.c=.s)
	$(AS) $(ASFLAGS) $(<:.c=.s) -o $@

%.o: %.asm Makefile
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean

clean:
	-rm -f beagleOS.elf beagleOS.bin
	-rm -f *.o
	-rm -f src/*.o
	-rm -f src/*.s
