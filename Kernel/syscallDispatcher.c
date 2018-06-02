#include <stdint.h>
#include "videoDriver.h"
#include "syscallDispatcher.h"
#include "rtc.h"
#include "std_buffers.h"
#include <lib.h>


typedef (*systemCall)();

systemCall sysCalls[] = { 0, 0, 0,
  (systemCall)_writePixel,
  (systemCall)_readPixel,
  (systemCall)_getScreenWidth,
  (systemCall)_getScreenHeight,
  (systemCall)_write,
  (systemCall)_read,
  (systemCall)_clearBuffer,
  (systemCall)_readTime
};

void syscallDispatcher(uint64_t index, uint64_t a, uint64_t b, uint64_t c){
  sysCalls[index](a, b, c);
}

void _writePixel(uint64_t width, uint64_t height, struct RGB color){
  writePixel(width, height, color);
}

void _readPixel(uint64_t width, uint64_t height, struct RGB * color){
  *color = readPixel(width,height);
}

uint64_t _getScreenWidth(){
  return getWidth();
}

uint64_t _getScreenHeight(){
  return getHeight();
}

void _write(uint64_t buffer, char c){
  writeCharBuffer(buffer, c);
}

uint64_t _read(uint64_t buffer){
  return (uint64_t)readCharBuffer(buffer);
}

uint64_t _clearBuffer(uint64_t index){
  clearBuffer(index);
  return 0;
}

uint64_t _readTime(uint64_t time) {
  if(time == 0)
    return getSeconds();
  if(time == 1)
    return getMinutes();
  if(time == 2)
    return getHour();
  return -1; //si me pasaron un parametro invalido
}
