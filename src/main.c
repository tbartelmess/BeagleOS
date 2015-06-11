#include "std.h"
//#include "stdio.h"

/* static void* exit_point = NULL; */
/* static void* exit_sp    = NULL; */

void kprintf(const char* str) {
    volatile void* UART0 = (void*)0x44E09000;
    volatile uint16_t* UART_LSR = (UART0 + 0x14);
    volatile uint16_t* UART_THR = (UART0 + 0x0);;

    while (*str) {
        while ((*UART_LSR & 0x20) == 0);
        const uint16_t car = *str;
        *UART_THR = car;
        str++;
    }
}

int main(__unused int argc, __unused char** argv) __attribute__ ((section(".text.bootme")));
int main(__unused int argc, __unused char** argv) {

    /* asm volatile ("mov r0, #0xa0000000\n\t" */
    /*               "sub r0, r0, #0x10000\n\t" */
    /*               "mov r1, sp\n\t" */
    /*               "mov sp, r0\n\t"); */

    /* void* volatile sp; */
    /* asm volatile ("mov %0, sp\n\t" */
    /*     	  : "=r" (sp)); */

    kprintf("\n\nHello, Mark Rada!\n\n");

    int derp = 0;
    asm volatile ("mov  %0, pc \n\t"
                  : "=r" (derp));

    return derp;
}
