#include "syscall.h"
#include "stdio.h"

void printf(char* format, ...){
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
}

void putchar(char c){
	write(_stdout);
}

char getchar(){
	read(_stdin);
}

void write(char c, int dest){
	syscall(_write, dest, c, 0, 0);
}

char read(int dest){
	syscall(_read, dest, c, 0, 0);
}
