#include <stdint.h>

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

struct RGB {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size);
void writeCharWithBackground(char c, uint64_t x, uint64_t y, struct RGB color,struct RGB background, uint64_t size);
void setSize(char s);
void putChar(char c, struct RGB color);
void printString(char * string, struct RGB color);
void clearScreen();
void writeInt(uint64_t num, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size);
void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size);

#endif
