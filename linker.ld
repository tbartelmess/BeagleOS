/* rammap */
MEMORY
{
    ram : ORIGIN = 0x402f0400, LENGTH = 0x10000
}
 
SECTIONS
{
    .text : { *(.text*) } > ram
}
