/* rammap */
ENTRY(_main)

SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x402f0400;
    _main = .;

    . = 0x80000000;
    _text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    _text_end = .;


}
