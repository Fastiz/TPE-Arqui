#include "syscall.h"
#include "stdlib.h"
#include "graphicClock.h"
#include "stdio.h"
#include "console.h"

#define MAX_SIZE 255

static void man(char * str);
static void echo(char * str);
static void time();
static void error();

static int compareString(char * str1, char * str2) {
	int i;
	char c1,c2;
	
	for(i = 0; str1[i] != 0 || str2[i] != 0; i++){
		if(str1[i] != str2[i])
			return 0;
	}
	return 1;
}

static void man(char * str) {
	unsigned char * div0 = "div0 - Tests division by zero exception.";
	unsigned char * echo = "echo - Prints string in standard output.";
	unsigned char * time = "time - Displays time in hour:minutes:seconds in standard output.";
	unsigned char * clock = "clock - Displays a digital clock in hour:minutes:seconds.";
	unsigned char * clear = "clear - Clear the screen";
	if(*str == 0){
		printf("This is the command mannual. The following commands are:\n%s\n%s\n%s\n%s\n%s",div0,echo,time,clock,clear);
	}
	else{
		if(compareString(str,"echo") == 1)
			printf(echo);
		else if(compareString(str,"time") == 1)
			printf(time);
		else if(compareString(str,"div0") == 1)
			printf(div0);
		else if(compareString(str,"clock") == 1)
			printf(clock);
		else if(compareString(str,"clear") == 1)
			printf(clear);
		else
			error();
	}
}
static void echo(char * str){
	printf(str);
}

static void time(){
	char seconds[16] = {0};
	char minutes[16] = {0};
	char hour[16] = {0};
	intToChar(_syscall(_readTime,0),16,seconds);
	intToChar(_syscall(_readTime,1),16,minutes);
	intToChar(_syscall(_readTime,2),16,hour);
	printf("%s:%s:%s",hour,minutes,seconds);
}
static void error(){
	int i;
	char * errorMsg = "Command not recognized.";
	for(i = 0; errorMsg[i] != 0; i++)
		_syscall(_write,2,errorMsg[i]);
}

void commandDispatcher(char * commandLine) {
	int i,j;
	unsigned char command[MAX_SIZE] = {0};
	unsigned char parameter[MAX_SIZE] = {0};
	int readingCommand = 1;
	for(i = 0, j = 0; commandLine[i] != 0 && i < MAX_SIZE - 1 && j < MAX_SIZE - 1; i++){
		if(commandLine[i] == ' '){
			readingCommand = 0;
			command[i] = 0;
		}
		else if(readingCommand)
			command[i] = commandLine[i];
		else
			parameter[j++] = commandLine[i];

	}
	parameter[j] = 0;
	int div0;
	if(compareString(command,"man") == 1)
		man(parameter);
	else if(compareString(command,"echo") == 1)
		echo(parameter);
	else if(compareString(command,"time") == 1)
		time();
	else if(compareString(command,"div0") == 1){
		div0 = 1/0;
		return;
	}
	else if(compareString(command,"frog") == 1)
		printf("     @..@        \n    (\\--/)      \n   (.>__<.)               \n   ^^^  ^^^");
	else if(compareString(command,"clock")==1)
		drawClock();
	else if(compareString(command,"clear")==1)
		resetConsole();
	else{
		error();
	}
}
