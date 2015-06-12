#include "std.h"
#include "vt100.h"
#include "beagle.h"
#include "am335x.h"

#ifndef __BUILD_NUM__
#define __BUILD_NUM__ 0
#endif

/* static void* exit_point = NULL; */
/* static void* exit_sp    = NULL; */

char kgetc() {
    while ((*UART_LSR & UART_LSR_RXFIFOE) == 0);
    const uint16_t car = *UART_RHR;
    return car;
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


    *UART_LCR = 0xC3;

    *UART_IER = 0;
    *UART_DLL = 0;
    *UART_DLH = 0;

    *UART_FCR = 0;

    *UART_DLL = 26; // baud_clock_hz / (16 * serial_tty_speed_bits)
    *UART_LCR = 3;


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

    return 42;
}
