#include <stdint.h>
#include "videoDriver.h"
#include "syscallDispatcher.h"
#include "rtc.h"
#include "std_buffers.h"
#include <lib.h>


typedef (*systemCall)();

systemCall sysCalls[] = { 0, 0, 0,
  _writePixel,
  _readPixel,
  _getScreenWidth,
  _getScreenHeight,
  /*_writeBuffer,
  _readBuffer,
  _clearBuffer,*/
  _readTime
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
/*
uint64_t _writeBuffer(uint64_t index, uint64_t str, uint64_t trash1, uint64_t trash2){
  return writeBuffer(index, (char *) str);
}

uint64_t _readBuffer(uint64_t index, uint64_t trash1, uint64_t trash2, uint64_t trash3){
  return (uint64_t)readBuffer(index);
}

uint64_t _clearBuffer(uint64_t index, uint64_t trash1, uint64_t trash2, uint64_t trash3){
  clearBuffer(index);
  return 0;
}*/

uint64_t _readTime(uint64_t time) {
  if(time == 0)
    return getSeconds();
  if(time == 1)
    return getMinutes();
  if(time == 2)
    return getHour();
  return -1; //si me pasaron un parametro invalido
}
