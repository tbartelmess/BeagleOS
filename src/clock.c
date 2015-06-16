#include "clock.h"
#include "am335x.h"

void
clock_init() {
    *DTIMER_TCLR = 0;

    // clock is uint32_t value; at 160 nanoseconds between ticks,
    // so we get 3,750,000,000 ticks in 10 minutes (which is my
    // arbitrary cycle for the timer); there is no way to set
    // the overflow value, but you can set the start value, so
    // we want to set the start value to be
    // UINT32_MAX - 3,750,000,000
    *DTIMER_TLDR = 544967295; // start at 1 million ticks
    *DTIMER_TCRR = 544967295; // reset to 1 million ticks

    *DTIMER_TCLR =
        DTIMER_TCLR_ST | DTIMER_TCLR_AR | DTIMER_TCLR_PRE | DTIMER_TCLR_PTV1;
}

void
clock_deinit() {
    // nothing right now...
}

uint32_t
clock() {
    return *DTIMER_TCRR;
}
