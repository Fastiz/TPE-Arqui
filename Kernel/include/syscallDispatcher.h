#include <lib.h>

void syscallDispatcher(uint64_t index, uint64_t a, uint64_t b, uint64_t c);
void _writePixel(uint64_t width, uint64_t height, struct RGB color);
void _readPixel(uint64_t width, uint64_t height, struct RGB * color);
void _write(uint64_t buffer, char c);
uint64_t _read(uint64_t buffer);
uint64_t _getScreenWidth();
uint64_t _getScreenHeight();
uint64_t _writeBuffer(uint64_t index, uint64_t str);
uint64_t _readBuffer(uint64_t index);
uint64_t _clearBuffer(uint64_t index);
uint64_t _readTime(uint64_t time);
void _scrollScreen(uint64_t ammount, struct RGB background);
void _replaceColor(struct RGB colorOld, struct RGB colorNew);