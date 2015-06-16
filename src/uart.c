#include "uart.h"
#include "am335x.h"

void
uart_init() {
    *UART_LCR = 0xC3; // unlock config registers

    *UART_IER = 0; // disable interrupts for now
    *UART_DLL = 0; // unlock the FIFO control register
    *UART_DLH = 0;

    *UART_FCR = 0; // try to disable FIFO stuff

    // Calculate DLL as:
    // baud_clock_hz / (16 * serial_tty_speed_bits)
    // clock rate for our hardware is 48MHz, and
    // serial TTY speed is 115200 bit/s
    *UART_DLL = 26; // lock the FIFO control register
    *UART_LCR = 3; // enable everything again
}

void
uart_deinit() {
    // TODO: do we need to undo anything to make u-boot work again?
}
