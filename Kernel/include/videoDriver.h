#include <stdint.h>
#include <lib.h>
uint64_t getWidth();
uint64_t getHeight();
void writePixel(uint64_t width, uint64_t height, struct RGB color);
struct RGB readPixel(uint64_t width, uint64_t height);
void movePixelsUp(uint64_t ammount,struct RGB background);
void replaceColor(struct RGB colorOld, struct RGB colorNew);
void backupScreen();
void restoreScreen();
void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t sizeX,uint64_t sizeY);
