#include "std.h"
#include "vt100.h"
#include "clock.h"
#include "uart.h"
#include "beagle.h"
#include "am335x.h"
#include "cpu.h"

#ifndef __BUILD_NUM__
#define __BUILD_NUM__ 0
#endif

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
    vt_init();

    // TODO: move this init code elsewhere
    ksyslog(LOG_INFO,
            "Welcome to " COLOUR(RED) "BeagleOS" COLOUR_RESET " "
            "(Build " COLOUR(GREEN) "%d" COLOUR_RESET ")",
            __BUILD_NUM__);

    char msg[1024];
    char* ptr = msg;
    ptr = vt_goto_home(ptr);
    ptr = sprintf(ptr, ascii_beagle);
    kprintf(msg, ptr - msg);

    bool quit = false;
    while (!quit) {
       const char input = kgetc();

       switch (input) {
       case 'q':
	 quit = true;
	 break;
       case 't':
	 debug_interrupt_vector_table();
	 break;
       case 'd':
	 debug_cpsr();
	 debug_spsr();
	 break;
       case 'i':
	 asm volatile ("    mrs     r0, CPSR\n\t"
		       "    bic     r0, r0, #0x0F\n\t"
		       "    orr     r0, r0, #0x10\n\t"
		       "    msr     CPSR_c, r0\n\t"
		       "    swi     5");
	 break;
       default:
	 ksyslog(LOG_INFO, "%c", input);
       }
    }

    vt_deinit();
    uart_deinit();
    clock_deinit();

    return 42;
}
