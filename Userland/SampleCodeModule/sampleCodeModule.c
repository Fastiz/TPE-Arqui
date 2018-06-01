#include "syscall.h"
#include "consoleScreen.h"
/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;


int main() {
	struct RGB color2 = {255, 0, 0};

	_syscall(3, 200,200,(uint64_t)&color2,0);


	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
