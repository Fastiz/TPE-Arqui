#include <stdint.h>
#include "videoDriver.h"


typedef (uint64_t(*func)(uint64_t, uint64_t, uint64_t, uint64_t));

uint64_t _writePixel(uint64_t width, uint64_t height, uint64_t color, uint64_t trash1){
  writePixel(width, height, (struct RGB) color);
  return 0;
}

uint64_t _readPixel(uint64_t width, uint64_t height, uint64_t trash1, uint64_t trash2){
  return (uint64_t) readPixel(width, height);
}

uint64_t _getWidth(uint64_t trash1, uint64_t trash2, uint64_t trash3, uint64_t trash4){
  return getWidth();
}

uint64_t _getHeight(uint64_t trash1, uint64_t trash2, uint64_t trash3, uint64_t trash4){
  return getHeight();
}

uint64_t _writeBuffer(uint64_t index, uint64_t str, uint64_t trash1, uint64_t trash2){
  return writeBuffer(index, (char *) str);
}

uint64_t _readBuffer(uint64_t index, uint64_t trash1, uint64_t trash2, uint64_t trash3){
  return (uint64_t)readBuffer(index);
}

uint64_t _clearBuffer(uint64_t index, uint64_t trash1, uint64_t trash2, uint64_t trash3){
  clearBuffer(index);
  return 0;
}
