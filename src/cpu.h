#pragma once

#include <std.h>

typedef enum {
    USER       = 0x10,
    FIQ        = 0x11,
    IRQ        = 0x12,
    SUPERVISOR = 0x13,
    ABORT      = 0x16,
    UNDEFINED  = 0x1B,
    SYSTEM     = 0x1F
} pmode;

pmode processor_mode(void);
void  debug_cpsr(void);
void  debug_spsr(void);
void  debug_interrupt_vector_table(void);
