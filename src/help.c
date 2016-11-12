#include <vt100.h>

void print_help() {
    ksyslog(LOG_INFO,
            "'q' Quit\n\r"
            "'t' Print Interrupt Table\n\r"
            "'d' Print Current Program Saved Program Status Registers\n\r"
            "'i' Send System Call 9\n\r"
            "'h' Print this help\n\n\r");
}
