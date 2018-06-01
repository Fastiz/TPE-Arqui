#include <stdint.h>
#include <videoDriver.h>


typedef (uint64_t(*func)(uint64_t, uint64_t, uint64_t, uint64_t));
static const func handlers[] = {getWidth, getHeight, readPixel, writePixel};

void syscallDispatcher(uint64_t offset){
  handlers[offset]();
}
