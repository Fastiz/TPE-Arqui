#include <stdint.h>
#include <lib.h>
uint64_t getWidth();
uint64_t getHeight();
void writePixel(uint64_t width, uint64_t height, struct RGB color);
struct RGB readPixel(uint64_t width, uint64_t height);
