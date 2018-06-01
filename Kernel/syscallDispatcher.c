#include <stdint.h>
#include "videoDriver.h"
#include "syscallDispatcher.h"
#include "rtc.h"
#include "std_buffers.h"


typedef uint64_t(*systemCall)(uint64_t a, uint64_t b, uint64_t c, uint64_t d);

systemCall sysCalls[] = { 0, 0, 0,
  _writePixel,
  _readPixel,
  _getWidth,
  _getHeight,
  _writeBuffer,
  _readBuffer,
  _clearBuffer,
  _readTime
};

void syscallDispatcher(uint64_t index, uint64_t a, uint64_t b, uint64_t c, uint64_t d){
  sysCalls[index](a, b, c, d);
}

uint64_t _writePixel(uint64_t width, uint64_t height, uint64_t color, uint64_t trash1){
  writePixel(width, height, &color);
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

uint64_t _readTime(uint64_t time, uint64_t trash1, uint64_t trash2, uint64_t trash3) {
  if(time == 0)
    return getSeconds();
  if(time == 1)
    return getMinutes();
  if(time == 2)
    return getHour();
  return -1; //si me pasaron un parametro invalido
}
