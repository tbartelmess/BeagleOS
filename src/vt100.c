#include "vt100.h"
#include "clock.h"

void vt_init() {
    char buffer[32];
    char* ptr = buffer;

    ptr = vt_clear_screen(ptr);
    ptr = vt_hide_cursor(ptr);

    ptr = vt_set_scroll_region(ptr, LOG_HOME, 80);
    ptr = vt_goto(ptr, LOG_HOME, 1);
    ptr = vt_save_cursor(ptr);

    kprintf(buffer, ptr - buffer);
}

void vt_deinit() {
    char buffer[64];
    char* ptr = buffer;

    ptr = vt_reset_scroll_region(ptr);
    ptr = vt_unhide_cursor(ptr);
    ptr = sprintf_string(ptr, "\nSHUTTING DOWN");
    kprintf(buffer, ptr - buffer);
}

char* vt_clear_screen(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "2J");
}

char* vt_goto_home(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "H");
}

static char* vt_set_location(char* buffer, const int first, const int second) {
    /* assert(first >= 0 && first < 100, */
    /*        "vt_set_location first is invalid (%d)", first); */
    /* assert(second >= 0 &&second < 100, */
    /*        "vt_set_loaction second is invalid (%d)", second); */

    const char first_high  = (char)(first / 10)  + '0';
    const char first_low   = (char)(first % 10)  + '0';
    const char second_high = (char)(second / 10) + '0';
    const char second_low  = (char)(second % 10) + '0';

    buffer = sprintf_string(buffer, ESC_CODE);
    if (first_high > 48)
	buffer = sprintf_char(buffer, first_high);
    buffer = sprintf_char(buffer, first_low);
    buffer = sprintf_char(buffer, ';');
    if (second_high > 48)
	buffer = sprintf_char(buffer, second_high);
    return sprintf_char(buffer, second_low);
}

char* vt_goto(char* buffer, const int row, const int column) {
    buffer = vt_set_location(buffer, row, column);
    return sprintf_char(buffer, 'H');
}

char* vt_hide_cursor(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "?25l");
}

char* vt_unhide_cursor(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "?25h");
}

char* vt_kill_line(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "K");
}

char* vt_reverse_kill_line(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "1K");
}

char* vt_set_scroll_region(char* buffer, int start, int end) {
    buffer = vt_set_location(buffer, start, end);
    return sprintf_char(buffer, 'r');
}

char* vt_reset_scroll_region(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "r");
}

char* vt_scroll_up(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "1S");
}

char* vt_scroll_down(char* buffer) {
    return sprintf_string(buffer, ESC_CODE "1T");
}

char* vt_save_cursor(char* buffer) {
    return sprintf_string(buffer, ESC "7");
}

char* vt_restore_cursor(char* buffer) {
    return sprintf_string(buffer, ESC "8");
}

static inline
char* log_priority(char* buffer, const int priority) {
    switch (priority) {
    case LOG_EMERG:
        return sprintf_string(buffer, "[" COLOUR(BG_RED) COLOUR(BLACK) "EMERGENCY:" COLOUR_RESET);
    case LOG_ALERT:
        return sprintf_string(buffer, "[" COLOUR(BG_RED) COLOUR(WHITE) "ALERT:" COLOUR_RESET);
    case LOG_CRIT:
        return sprintf_string(buffer, "[" COLOUR(BG_LIGHT_RED) COLOUR(WHITE) "CRITICAL:" COLOUR_RESET);
    case LOG_ERR:
        return sprintf_string(buffer, "[" COLOUR(RED) "ERROR:" COLOUR_RESET);
    case LOG_WARNING:
        return sprintf_string(buffer, "[" COLOUR(YELLOW) "WARNING:" COLOUR_RESET);
    case LOG_NOTICE:
        return sprintf_string(buffer, "[" COLOUR(GREEN) "NOTICE:" COLOUR_RESET);
    case LOG_INFO:
        return sprintf_string(buffer, "[" COLOUR(BLUE) "INFO:" COLOUR_RESET);
    case LOG_DEBUG:
        return sprintf_string(buffer, "[" COLOUR(LIGHT_BLUE) "DEBUG:" COLOUR_RESET);
    }

    return buffer;
}

char* log_start(char* buffer, const int priority) {
    buffer = vt_restore_cursor(buffer);
    buffer = log_priority(buffer, priority);
    buffer = sprintf_uint(buffer, clock());
    return sprintf_string(buffer, "]: ");
}

char* log_end(char* buffer) {
    buffer = sprintf_string(buffer, "\r\n");
    return vt_save_cursor(buffer);
}

void ksyslog(__unused const int priority, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[256];
    char* ptr = buffer;

    ptr = log_start(ptr, priority);
    ptr = sprintf_va(ptr, fmt, args);
    ptr = log_end(ptr);

    kprintf(buffer, ptr - buffer);
    va_end(args);
}
