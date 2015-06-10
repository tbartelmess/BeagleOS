.equ    UART0,          0x44E09000      /* UART0 register */
.equ    UART_LSR_UART,  0x14
.equ    UART_THR,       0x0
.section ".text.boot"
.global _start

_start:
   mov r0,#'E'
   and     r0, r0, #0xFF
   ldr r1, =UART0
1:
        ldrh    r2, [r1, #UART_LSR_UART]
        and     r2, r2, #0x20
        cmp     r2, #0
        beq     1b
2:
        strh    r0, [r1, #UART_THR]
        mov     pc, lr
