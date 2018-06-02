#include <stdint.h>

struct RGB{
  char red;
  char green;
  char blue;
};

void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t size);

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size);

void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, uint64_t size);

void fillScreen(struct RGB color);

void clearScreen();

void moveScreenUp(uint64_t size, uint64_t ammount, struct RGB background);

void backupScreen();

void restoreScreen();
