#include <vt100.h>

void print_help() {
    ksyslog(LOG_INFO,
            "\n\r"
            "'q' Quit\n\r"
            "'t' Print Interrupt Table\n\r"
            "'d' Print Current Program Saved Program Status Registers\n\r"
            "'p' Try the pass() syscall\n\r"
            "'r' REBOOT\n\r"
            "'h' Print this help\n\n\r");
}
