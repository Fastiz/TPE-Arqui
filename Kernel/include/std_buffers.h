#define STD_OUT 0
#define STD_IN 1
#define STD_ERR 2

void setUpBuffers();
void clearBuffer(int index);
int writeCharBuffer(int index, char character);
int writeIntBuffer(int index, int value,int base);
int writeStrBuffer(int index, char * str);
char readCharBuffer(int index);
int readStrBuffer(int index, char * str,int size);
