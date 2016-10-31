#include "cpu.h"
#include "vt100.h"
#include "irq.h"

#define CPU_MODE_MASK             0x0000001f

#define THUMB_STATUS_MASK         0x00000020
#define FIQ_STATUS_MASK           0x00000040
#define IRQ_STATUS_MASK           0x00000080
#define ABORT_STATUS_MASK         0x00000100

#define FLAG_NEGATIVE_MASK        0x80000000
#define FLAG_ZERO_MASK            0x40000000
#define FLAG_CARRY_MASK           0x20000000
#define FLAG_OVERFLOW_MASK        0x10000000
#define FLAG_STICKY_OVERFLOW_MASK 0x08000000

static inline const char* processor_mode_string(uint32_t status) {
    switch (status & CPU_MODE_MASK) {
    case USER:       return "user";
    case FIQ:        return "fiq";
    case IRQ:        return "irq";
    case SUPERVISOR: return "supervisor";
    case ABORT:      return "abort";
    case UNDEFINED:  return "undefined";
    case SYSTEM:     return "system";
    default:         return "ERROR";
    }
}

static inline bool thumb_state(const uint32_t status) { return (status & THUMB_STATUS_MASK);     }
static inline bool   fiq_state(const uint32_t status) { return (status & FIQ_STATUS_MASK);       }
static inline bool   irq_state(const uint32_t status) { return (status & IRQ_STATUS_MASK);       }
static inline bool abort_state(const uint32_t status) { return (status & ABORT_STATUS_MASK);     }

static inline bool cc_n(const uint32_t status) { return (status & FLAG_NEGATIVE_MASK);        }
static inline bool cc_z(const uint32_t status) { return (status & FLAG_ZERO_MASK);            }
static inline bool cc_c(const uint32_t status) { return (status & FLAG_CARRY_MASK);           }
static inline bool cc_v(const uint32_t status) { return (status & FLAG_OVERFLOW_MASK);        }
static inline bool cc_s(const uint32_t status) { return (status & FLAG_STICKY_OVERFLOW_MASK); }

static void _debug_psr(const char* const name, const uint32_t status) {

    ksyslog(LOG_INFO,
	    "%s Information\r\n"
	    "       Current Mode: %s\n\r"
	    "        Thumb State: %s\n\r"
	    "        FIQ Enabled: %s\n\r"
	    "        IRQ Enabled: %s\n\r"
	    "      Abort Enabled: %s\n\r"
	    "    Condition Codes: %c %c %c %c %c",
	    name,
	    processor_mode_string(status),
	    thumb_state(status) ? "Yes" : "No",
	    fiq_state(status)   ? "No"  : "Yes",
	    irq_state(status)   ? "No"  : "Yes",
	    abort_state(status) ? "No"  : "Yes",
	    cc_n(status) ? 'N' : '_',
	    cc_z(status) ? 'Z' : '_',
	    cc_c(status) ? 'C' : '_',
	    cc_v(status) ? 'V' : '_',
	    cc_s(status) ? 'S' : '_');
}

/**
 * http://www.heyrick.co.uk/armwiki/The_Status_register
 */
void debug_cpsr(void) {
    uint32_t status;
    asm("mrs %0, cpsr" : "=r" (status));
    _debug_psr("CPSR", status);
}

void debug_spsr(void) {
    uint32_t status;
    asm("mrs %0, spsr" : "=r" (status));
    _debug_psr("SPSR", status);
}

pmode processor_mode() {
    uint32_t status;
    asm("mrs %0, cpsr" : "=r" (status));

    return (status & CPU_MODE_MASK);
}

void debug_interrupt_vector_table() {

    const uint32_t base = vector_table;

    ksyslog(LOG_INFO,
	    "Interrupt Table\r\n"
	    "    Undefined Instruction: %x\n\r"
	    "       Software Interrupt: %x\n\r"
	    "           Prefetch Abort: %x\n\r"
	    "               Data Abort: %x\n\r"
	    "                      IRQ: %x\n\r"
	    "                      FIQ: %x\n\n\r"
	    "Default Interrupt Address:\r\n"
	    "    Undefined Instruction: %x\n\r"
	    "       Software Interrupt: %x\n\r"
	    "           Prefetch Abort: %x\n\r"
	    "               Data Abort: %x\n\r"
	    "                      IRQ: %x\n\r"
	    "                      FIQ: %x\n\n",
	    base + 0x4,
	    base + 0x8,
	    base + 0xC,
	    base + 0x10,
	    // NOTE: we skip 0x14 because it is apparently unused/reserved
	    base + 0x18,
	    base + 0x1C,
	    base + 0x20,
	    base + 0x24,
	    base + 0x28,
	    base + 0x2C,
	    base + 0x34,
	    base + 0x38);
}
