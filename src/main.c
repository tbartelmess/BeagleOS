#include "std.h"
#include "vt100.h"
#include "clock.h"
#include "uart.h"
#include "am335x.h"
#include "cpu.h"
#include "irq.h"
#include "help.h"
#include "version.h"
#include "bgsh.h"


/* static void* exit_point = NULL; */
/* static void* exit_sp    = NULL; */

int main(__unused int argc, __unused char** argv) __attribute__ ((section(".text.bootme")));
int main(__unused int argc, __unused char** argv) {

    /* asm volatile ("mov r0, #0xa0000000\n\t" */
    /*               "sub r0, r0, #0x10000\n\t" */
    /*               "mov r1, sp\n\t" */
    /*               "mov sp, r0\n\t"); */

    /* void* volatile sp; */
    /* asm volatile ("mov %0, sp\n\t" */
    /*     	  : "=r" (sp)); */


    clock_init();
    uart_init();
    irq_init();

    // go to user land/mode
    asm volatile ("    mrs     r0, CPSR\n\t"
		  "    bic     r0, r0, #0x0F\n\t"
		  "    orr     r0, r0, #0x10\n\t"
		  "    msr     CPSR_c, r0\n\t");

    // Drop into the beagle shell
    bgsh_main();

    irq_deinit();
    vt_deinit();
    uart_deinit();
    clock_deinit();

    return 42;
}
