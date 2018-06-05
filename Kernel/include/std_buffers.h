#include <stdint.h>

#ifndef STD_BUFFERS_H
#define STD_BUFFERS_H

#define STD_OUT 1
#define STD_IN 0
#define STD_ERR 2

void setUpBuffers();
void clearBuffer(int index);
int writeCharBuffer(int index, char character);
int writeIntBuffer(int index, uint64_t value,int base);
int writeStrBuffer(int index, char * str);
char readCharBuffer(int index);
int readStrBuffer(int index, char * str,int size);

#endif
