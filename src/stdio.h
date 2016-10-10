#pragma once

#include "std.h"

/**
 * Similar to sprintf(3), except it only supports a subset of format specifiers.
 *
 * Also, this variation of sprintf returns a pointer to one character past the
 * end of the buffer segment that was used by the string. The string will not
 * be NULL-terminated, and so you should use this pointer to calculate the length
 * of the string.
 *
 * %d - signed decimal
 * %u - unsigned decimal
 * %o - unsigned octal
 * %x - unsigned hexidecimal
 * %p - pointer
 * %s - string (non-recursive)
 * %c - char
 * %% - literal `%'
 */
char* sprintf(char* buffer, const char* fmt, ...)
    __attribute__((format(printf, 2, 3)));

char* sprintf_va(char* buffer, const char* fmt, va_list args);

/**
 * TODO: need to separate kernel stuff from userland stuff eventually
 *
 * This will print the string over the serial line using a busy-wait
 * implementation, so it should only be used for debugging and interrupt
 * driven I/O is not available.
 */
void kprintf(const char* str, const size_t len);

// TODO: documentation
char kgetc();

// general number printing, reasonably fast, but special case
// code will still be faster
char* sprintf_int(char* buffer, const int32_t num);
char* sprintf_uint(char* buffer, const uint32_t num);
char* sprintf_hex(char* buffer, const uint32_t num);
char* sprintf_ptr(char* buffer, const void* const ptr);
char* sprintf_string(char* buffer, const char* str);

static inline __unused char* sprintf_char(char* buffer, const char c) {
    *buffer = c;
    return ++buffer;
}
