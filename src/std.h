#define NULL 0

typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef uint32_t size_t;
typedef int32_t ssize_t;

typedef char bool;
#define true 1
#define false 0

#define __unused __attribute__ ((unused))

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
