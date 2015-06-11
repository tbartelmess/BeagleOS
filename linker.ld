ENTRY(main)

MEMORY
{
    RAM  : ORIGIN = 0x80000000, LENGTH = 512M
}

SECTIONS
{
        /* Starts at LOADER_ADDR. */
        _start = . ;

        .text :
        {
                *(.text.bootme*)
                *(.text*)
        } > RAM

        . = ALIGN(4); /* align to page size */
        .data : /* Initialized data. */
        {
              *(.data*)
        } > RAM

        . = ALIGN(4); /* align to page size */
        .bss : /* Uninitialized data. */
        {
              *(.bss*)
              *(.sbss*)
        } > RAM

        . = ALIGN(4); /* align to page size */
        .rodata :
        {
              *(.rodata*)
        } > RAM

        _end = . ;
}
