#define STD_OUT 0
#define STD_IN 1
#define STD_ERR 2

void clearBuffer(int index);
int writeCharBuffer(int index, char character);
int writeStrBuffer(int index, char * str);
char * readBuffer(int index);