#include <stdint.h>

struct RGB {
	char red;
	char green;
	char blue;
};

void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t size);
void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size);
void setSize(char s);
void putChar(char c, struct RGB color);
void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, uint64_t size);
void printString(char * string, struct RGB color);
void fillScreen(struct RGB color);
void clearScreen();
void moveScreenUp();
