#include "std.h"
#include "vt100.h"
#include "clock.h"
#include "uart.h"
#include "beagle.h"

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

    while (1) {
       const char input = kgetc();
       if (input == 'q') break;
       ksyslog(LOG_INFO, "%c", input);
    }

    vt_deinit();
    uart_deinit();
    clock_deinit();

    return 42;
}
