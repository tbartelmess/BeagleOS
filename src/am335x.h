#ifndef __AM335X_H__
#define __AM335X_H__

#include "std.h"

#define HWREG(x) (*((volatile uint32_t*)(x)))

// Serial I/O (UART0)

#define UART0 (volatile uint8_t*)0x44E09000
#define UART_DLL UART0
#define UART_THR UART0
#define UART_RHR UART0
#define UART_DLH (UART0 + 4)
#define UART_IER (UART0 + 4)
#define UART_EFR (UART0 + 8)
#define UART_FCR (UART0 + 8)
#define UART_LCR (UART0 + 12)
#define UART_LSR (UART0 + 20)
#define UART_SSR (UART0 + 44)

enum {
    UART_LSR_RXFIFOE   = 0x1,
    UART_LSR_TXSRE     = 0x20
} UART_LSR_BITS;

enum {
    UART_SSR_TXFIFOFULL = 0x1
} UART_SSR_BITS;


// Main Clock (DMTIMER1)

#define DMTIMER 0x44E05000
#define DMTIMER_TCLR (DMTIMER + 0x38) // control

enum {
    DMTIMER_TCLR_ST    = 1,
    DMTIMER_TCLR_AR    = 2,
    DMTIMER_TCLR_PTV1  = 4,
    DMTIMER_TCLR_PTV2  = 8,
    DMTIMER_TCLR_PTV3  = 16,
    DMTIMER_TCLR_PRE   = 32
} DMTIMER_TCLR_BITS;

#define DMTIMER_TCRR (DMTIMER + 0x3C) // value
#define DMTIMER_TLDR (DMTIMER + 0x40) // load value


// Watch Dog

#define WDT 0x44E35000
#define WDT_WTGR (WDT + 0x30)
#define WDT_WWPS (WDT + 0x38)

enum {
    WDT_WWPS_W_PEND_WSPR = 0x10
} WDT_WWPS_BITS;

#define WDT_WSPR (WDT + 0x48)
