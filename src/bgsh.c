#include "vt100.h"
#include "version.h"
#include "beagle.h"



static void
print_header() {
    ksyslog(LOG_INFO,
            "Welcome to " COLOUR(RED) "BeagleOS" COLOUR_RESET " "
            "(Build " COLOUR(GREEN) "%d" COLOUR_RESET ")",
            __BUILD_NUM__);
    char msg[1024];
    char* ptr = msg;
    ptr = vt_goto_home(ptr);
    ptr = sprintf(ptr, ascii_beagle);
    kprintf(msg, ptr - msg);
}

void bgsh_main() {
    vt_init();
    print_header();
}
