#ifndef __VT100_H__
#define __VT100_H__

#include "std.h"
#include "stdio.h"

#define ESC "\x1B"
#define ESC_CODE ESC "["

void vt_init(void);
void vt_deinit(void);

char* vt_clear_screen(char* buffer);
char* vt_goto_home(char* buffer);
char* vt_goto(char* buffer, const int row, const int column);
char* vt_hide_cursor(char* buffer);
char* vt_unhide_cursor(char* buffer);
char* vt_kill_line(char* buffer);
char* vt_reverse_kill_line(char* buffer);
char* vt_reset_scroll_region(char* buffer);
char* vt_set_scroll_region(char* buffer, int start, int end);
char* vt_save_cursor(char* buffer);
char* vt_restore_cursor(char* buffer);

// these do not seem to work...
char* vt_scroll_up(char* buffer);
char* vt_scroll_down(char* buffer);


// coloured output
#define BLACK          "30"
#define RED            "31"
#define GREEN          "32"
#define YELLOW         "33"
#define BLUE           "34"
#define MAGENTA        "35"
#define CYAN           "36"
#define LIGHT_GRAY     "37"
#define DARK_GRAY      "90"
#define LIGHT_RED      "91"
#define LIGHT_GREEN    "92"
#define LIGHT_YELLOW   "93"
#define LIGHT_BLUE     "94"
#define LIGHT_MAGENTA  "95"
#define LIGHT_CYAN     "96"
#define WHITE          "97"

#define DEFAULT        "39"

#define BG_BLACK          "40"
#define BG_RED            "41"
#define BG_GREEN          "42"
#define BG_YELLOW         "43"
#define BG_BLUE           "44"
#define BG_MAGENTA        "45"
#define BG_CYAN           "46"
#define BG_LIGHT_GRAY     "47"
#define BG_DARK_GRAY      "100"
#define BG_LIGHT_RED      "101"
#define BG_LIGHT_GREEN    "102"
#define BG_LIGHT_YELLOW   "103"
#define BG_LIGHT_BLUE     "104"
#define BG_LIGHT_MAGENTA  "105"
#define BG_LIGHT_CYAN     "106"
#define BG_WHITE          "107"

#define COLOUR_RESET ESC_CODE "0m"
#define COLOUR_SUFFIX "m"
#define COLOUR(c) ESC_CODE c COLOUR_SUFFIX

#define vt_colour_reset(ptr) sprintf_string(ptr, COLOUR_RESET)


/**
 * The row where logging begins.
 */
#define LOG_HOME 10

/**
 * The row where logging ends.
 */
#define LOG_END  99

/**
 * To begin arbitrary logging (table, multiline things, etc.), use
 * vt_log_start() first, and then vt_log_end() to complete the
 * logging. Otherwise, use vt_log() with a format string for generic
 * logging as it is a wrapper around vt_log_start() and vt_log_end().
 */
char* log_start(char* buffer);
char* clog_start(const int time, char* buffer);
char* log_end(char* buffer);
void  syslog(const int priority, const char* fmt, ...);
void  ksyslog(const int priority, const char* fmt, ...);

#endif
