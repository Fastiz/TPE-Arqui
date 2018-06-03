#include <stdint.h>

int strcmp(char * str1, char* str2) {
	int i;
	char c1,c2;
	
	for(i = 0; str1[i] != 0 || str2[i] != 0; i++){
		if(str1[i] != str2[i])
			return 0;
	}
	return 1;
}

char * intToChar(int value,int base,char * buffer) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}