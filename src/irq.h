#include <std.h>

void irq_init(void);
void irq_deinit(void);

extern const uint32_t vector_table;

void syscall_handle(const int32_t code,
                    __unused const void* const req,
                    int* const sp);
