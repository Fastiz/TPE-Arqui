#include "syscall.h"
#include "consoleScreen.h"
#include "console.h"
/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;


int main() {
	/*struct RGB color2 = {255,0,0};
	_syscall(4,0,0,&color2);
	_syscall(3, 200,200,color2,0);
	_syscall(3, 500, 500,color2,0);*/
	console();

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
