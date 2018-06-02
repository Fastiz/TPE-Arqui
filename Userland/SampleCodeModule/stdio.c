#include "syscall.h"
#include "stdio.h"

/*void printf(char* format, ...){
	int parameterIndex;
	for(format; format != '0'; format++){
		if(format == '%'){
			format++;
			switch () {
				case d:
					break;

			}
		}else{
			putchar(format);
		}
	}
}*/

void putchar(char c){
  _syscall(_write, 1, c);
}

char getchar(){
	return _syscall(_read, 0);
}
