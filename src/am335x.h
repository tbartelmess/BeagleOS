#ifndef __AM335X_H__
#define __AM335X_H__

#include "std.h"

#define UART0 (volatile uint32_t*)0x44E09000
#define UART_DLL UART0
#define UART_THR UART0
#define UART_RHR UART0
#define UART_DLH (UART0 + 1)
#define UART_IER (UART0 + 1)
#define UART_EFR (UART0 + 2)
#define UART_FCR (UART0 + 2)
#define UART_LCR (UART0 + 3)
#define UART_LSR (UART0 + 5)
#define UART_SSR (UART0 + 11)

enum {
    UART_LSR_RXFIFOE   = 0x1,
    UART_LSR_TXSRE     = 0x20
} UART_LSR_BITS;

enum {
    UART_SSR_TXFIFOFULL = 0x1
} UART_SSR_BITS;

#endif
