#include "syscall.h"
#include "consoleScreen.h"
/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;


int main() {
	struct RGB color = {255, 0, 0};
	syscall(_writePixel, 10, 10, (uint64_t)&color, 0);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
