#include <stdint.h>

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

struct RGB {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size);
void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size);
void clearScreen();

#endif
