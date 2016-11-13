#pragma once

#include <std.h>


ssize_t pass(void);

ssize_t printf(const char* restrict fmt, ...)
    __attribute__ ((format(printf, 1, 2)));

char getc(void);

ssize_t getline(char** const line_buffer, size_t* const line_buffer_size);

void reboot(void) __attribute__ ((noreturn));
