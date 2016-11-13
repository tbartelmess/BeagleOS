#include <syscall.h>

enum syscall_id {
    syscall_pass       = 0,
    syscall_printf     = 1,
    syscall_getc       = 2,
    syscall_getline    = 3,
    syscall_reboot     = 4
};

struct printf_req {
    const char* restrict fmt;
};

struct getline_req {
    size_t* buffer_length;
    char**  buffer;
};


static inline
ssize_t
syscall(const enum syscall_id id, void* const syscall_arguments)
{
    asm volatile ("    mov     r0, %0\n\t"
                  "    mov     r1, %1\n\t"
                  "    svc     0"
                  :
                  : "r" (id), "r" (syscall_arguments)
                  : "r0", "r1", "r2", "r3", "memory");

    register ssize_t result asm ("r0");
    return result;
}


ssize_t pass(void) {
    return syscall(syscall_pass, NULL);
}

ssize_t printf(const char* restrict fmt, ...) {
    struct printf_req req = {
        .fmt = fmt
    };
    return syscall(syscall_printf, &req);
}

char getc(void) {
    return syscall(syscall_getc, NULL);
}

ssize_t getline(char** const line_buffer, size_t* const line_buffer_size) {
    struct getline_req req = {
        .buffer_length = line_buffer_size,
        .buffer = line_buffer
    };
    return syscall(syscall_getline, &req);
}

void reboot(void) {
    syscall(syscall_reboot, NULL);
    FOREVER;
}
