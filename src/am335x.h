#pragma once

#include "std.h"

// Serial I/O (UART0)

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


// Main Clock (DTIMER1)

#define DTIMER (volatile uint32_t*)0x44E05000
#define DTIMER_TCLR (DTIMER + 14) // control

enum {
    DTIMER_TCLR_ST    = 1,
    DTIMER_TCLR_AR    = 2,
    DTIMER_TCLR_PTV1  = 4,
    DTIMER_TCLR_PTV2  = 8,
    DTIMER_TCLR_PTV3  = 16,
    DTIMER_TCLR_PRE   = 32
} DTIMER_TCLR_BITS;

#define DTIMER_TCRR (DTIMER + 15) // value
#define DTIMER_TLDR (DTIMER + 16) // load value


// Watch Dog

#define WDT (volatile uint32_t*)0x44E35000
#define WDT_WTGR (WDT + 12)
#define WDT_WWPS (WDT + 13)

enum {
    WDT_WWPS_W_PEND_WSPR = 0x10
} WDT_WWPS_BITS;

#define WDT_WSPR (WDT + 18)

