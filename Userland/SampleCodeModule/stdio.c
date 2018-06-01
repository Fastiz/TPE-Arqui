#include "console.h"
#include "videoDriver.h"
#include "syscall.h"

extern int line, linePosition;

void printf(char* format, ...){
	int i = 0, parameterIndex;
	while(format != 0){
		if(format++ == '%'){
			if(format == 'd')
				// https://stackoverflow.com/questions/1735236/how-to-write-my-own-printf-in-c
		}
	}
}

void putchar(char c){

}
