ENTRY(main)

SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x80200000;

    .text :
    {
        *(.text.bootme*)
        *(.text*)
    }

    . = ALIGN(4096); /* align to page size */
    .data : /* Initialized data. */
    {
      *(.data*)
    }

    . = ALIGN(4096); /* align to page size */
    .bss : /* Uninitialized data. */
    {
      *(.bss*)
      *(.sbss*)
    }

    . = ALIGN(4096); /* align to page size */
    .rodata :
    {
      *(.rodata*)
    }
}
