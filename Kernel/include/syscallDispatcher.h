#include <lib.h>

#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H

void syscallDispatcher(uint64_t index, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
void _writePixel(uint64_t width, uint64_t height, struct RGB color);
void _writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t sizeX,uint64_t sizeY);
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
void _backupScreen();
void _restoreScreen();
void _fillScreen();
void _beep(uint64_t time);
void _activateBeep();
void _deactivateBeep();

#endif
