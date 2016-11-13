#include "irq.h"
#include "am335x.h"
#include "vt100.h"

#define NUM_INTERRUPTS 101

void swi_enter(void);

static void (*isr_map[NUM_INTERRUPTS])(void);

// NOTE: we should probably print the result of this out once so that we
//       do not have to look it up at runtime at each boot

const uint32_t vector_table = 0x9F74E000;

void syscall_handle(const int32_t code,
                    void* const req,
                    int* const sp) {

    switch (code) {
    case 4:
        ksyslog(LOG_ALERT, "REBOOTING!!!!!!!!");
        return;
    default:
        ksyslog(LOG_INFO,
                "GO TO HYPERSPACE, CHEWIE! Call %d with req %p",
                code,
                req);
        break;
    };

    asm volatile ("mov    r0, %0                                \n"
                  "msr	  cpsr, #0xDF            /* System */ \n"
                  "mov	  sp, r0                              \n"
                  "ldmfd  sp!, {r2-r11, lr}                     \n"
                  "msr    cpsr, #0xD3           /* Supervisor */\n"

                  "msr    spsr, r3                              \n"
                  "cmp    r2, #0                                \n"
                  "movnes pc, r2                                \n"

                  "msr    cpsr, #0xDF            /* System */   \n"
                  "mov    r0, sp                                \n"
                  "add    sp, sp, #20                           \n"
                  "msr    cpsr, #0xD3           /* Supervisor */\n"

                  "/* ^ acts like movs when pc is in list */    \n"
                  "ldmfd  r0, {r0,r2,r3,r12,pc}^                \n"
                  :
                  : "r" (sp)
                  : "r0");
}

void irq_init() {

    for (uint32_t i = 0; i < 3; i++) {
        HWREG(AINTC_ECR(i)) = AINTC_ECR_DISABLE;
        HWREG(AINTC_SECR(i)) = AINTC_SECR_ENABLE_STATUS;
    }

    HWREG(AINTC_HIER) &= ~(AINTC_HIER_IRQ | AINTC_HIER_FIQ);

    HWREG(AINTC_GER) = 0;

    HWREG(AINTC_VBR) = (uint32_t)isr_map;

    HWREG(AINTC_VSR) = 0;

    HWREG(vector_table + 0x24) = (uint32_t)swi_enter;
}

void irq_deinit() {
    // TODO: probably should reset things again
}
