#include <std.h>

void irq_init(void);
void irq_deinit(void);

uint32_t get_vectors_address(void);

void syscall_handle(const int32_t code,
                    __unused const void* const req,
                    int* const sp);
