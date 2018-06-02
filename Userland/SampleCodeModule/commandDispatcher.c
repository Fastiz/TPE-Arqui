#include "syscall.h"
#include "stdlib.h"

#define MAX_SIZE 255

static void echo(char * str);
static void time();
static void error();

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
	if(compareString(command,"echo") == 1)
		echo(parameter);
	else if(compareString(command,"time") == 1)
		time();
	else if(compareString(command,"frog") == 1)
		printf("     @..@        \n    (\\--/)      \n   (.>__<.)               \n   ^^^  ^^^");
	else{
		error();
	}
}

static void echo(char * str){
	int i;
	for(i = 0; str[i] != 0; i++)
		_syscall(_write,1,str[i]);
}
static void time(){
	char seconds[16] = {0};
	char minutes[16] = {0};
	char hour[16] = {0};
	intToChar(_syscall(_readTime,0),16,seconds);
	intToChar(_syscall(_readTime,1),16,minutes);
	intToChar(_syscall(_readTime,2),16,hour);

	int i;
	for(i = 0; hour[i] != 0; i++)
		_syscall(_write,1,hour[i]);
	_syscall(_write,1,':');

	for(i = 0; minutes[i] != 0; i++)
		_syscall(_write,1,minutes[i]);
	_syscall(_write,1,':');

	for(i = 0; seconds[i] != 0; i++)
		_syscall(_write,1,seconds[i]);
}
static void error(){
	int i;
	char * errorMsg = "Command not recognized.";
	for(i = 0; errorMsg[i] != 0; i++)
		_syscall(_write,2,errorMsg[i]);
}
int compareString(char * str1, char * str2) {
	int i;
	char c1,c2;
	for(i = 0; str1[i] != 0 || str2[i] != 0; i++){
		if(str1[i] != str2[i])
			return 0;
	}
	return 1;
}
