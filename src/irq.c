#include "irq.h"
#include "am335x.h"
#include "vt100.h"

#define NUM_INTERRUPTS 101

void swi_enter(void);

static void (*isr_map[NUM_INTERRUPTS])(void);

// NOTE: we should probably print the result of this out once so that we
//       do not have to look it up at runtime at each boot
uint32_t get_vectors_address() {
    uint32_t v;

    /* read SCTLR */
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0\n"
			 : "=r" (v) : : );
    if (v & (1<<13))
        return (uint32_t)0xffff0000;

    /* read VBAR */
    __asm__ __volatile__("mrc p15, 0, %0, c12, c0, 0\n"
			 : "=r" (v) : : );
    return (uint32_t)v;
}

void syscall_handle(__unused const int32_t code,
                    __unused const void* const req,
                    int* const sp) {

  //  ksyslog(LOG_INFO, "code = %d\t\tsp = %p", code, sp);
  //  ksyslog(LOG_INFO, "GO TO HYPERSPACE, CHEWIE!");

   asm volatile ("mov    r0, %0                                \n"
		 "msr	  cpsr, #0xDF             /* System */  \n"
		 "mov	  sp, r0                                \n"
		 "ldmfd  sp!, {r0-r11, lr}                     \n"
		 "msr    cpsr, #0xD3		/* Supervisor */\n"

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

  uint32_t const interrupt_vector = get_vectors_address();
  HWREG(interrupt_vector + 0x8) = (0xea000000 | (((uint32_t)swi_enter >> 2) - 4));
}

void irq_deinit() {
  // TODO: probably should reset things again
}
