#include "clock.h"
#include "am335x.h"

void
clock_init() {
    HWREG(DMTIMER_TCLR) = 0;

    // clock is uint32_t value; at 160 nanoseconds between ticks,
    // so we get 3,750,000,000 ticks in 10 minutes (which is my
    // arbitrary cycle for the timer); there is no way to set
    // the overflow value, but you can set the start value, so
    // we want to set the start value to be
    // UINT32_MAX - 3,750,000,000
    HWREG(DMTIMER_TLDR) = 544967295; // start at 1 million ticks
    HWREG(DMTIMER_TCRR) = 544967295; // reset to 1 million ticks

    for (volatile size_t i = 0; i < 2; ++i)
        HWREG(DMTIMER_TCLR) = DMTIMER_TCLR_ST  |
	                      DMTIMER_TCLR_AR  |
	                      DMTIMER_TCLR_PRE |
	                      DMTIMER_TCLR_PTV1;
}

void
clock_deinit() {
    // nothing right now...
}

uint32_t
clock() {
    return HWREG(DMTIMER_TCRR);
}
