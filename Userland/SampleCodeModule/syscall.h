#include <stdint.h>

#define _getWidth 3
#define _getHeight 4
#define _writePixel 3
#define _readPixel 6
#define _write 7
#define _read 8


uint64_t syscall(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
