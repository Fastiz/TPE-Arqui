#include "syscall.h"
#include "stdio.h"
#include <stdarg.h>

void printf(char* format, ...){
  va_list arg;
  va_start(arg, format);
  int i;
  char* s;
	for(format; *format != 0; format++){
		if(*format == '%'){
			format++;
      switch(*format){
            case 'c' :
              i = va_arg(arg,int);
              putchar(i);
              break;

            case 'd' :
              i = va_arg(arg,int);
              if(i<0){
                i = -i;
                putchar('-');
              }
          int j=1;
          for(;i>=j;j*=10){};

          for(j/=10; j > 0; j/=10){
            putchar(i/j+'0');
            i%=j;
          }

          break;

          case 's':
            s = va_arg(arg,char*);
            while(*s){
              putchar(*s);
              s++;
            }
            break;
        }
      }else{
        putchar(*format);
      }

     }
}

void putchar(char c){
  _syscall(_write, 1, c);
}

char getchar(){
	return _syscall(_read, 0);
}
