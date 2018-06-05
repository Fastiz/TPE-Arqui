#include <syscall.h>
#include <font.h>
#include <stdint.h>
#include <screenManager.h>


void writeCharWithBackground(char c, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size){
	if(c < 32 || c > 255) //falta ver el limite de c, no es 255 en esta fuente
		return;

	 char * posOfChar = getCharPos(c);
	for(int j = 0; j < CHAR_HEIGHT ; j++) {
		for(int i = 0, k = 128; i < CHAR_WIDTH; i++, k/=2){
			if(k & posOfChar[j])
				_syscall(_writeBlock,i*size + x, j*size + y, color,size,size);
			else
				_syscall(_writeBlock,i*size + x, j*size + y, background,size,size);
		}
	}
}

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size){
	if(c < 32 || c > 255) //falta ver el limite de c, no es 255 en esta fuente
		return;
	//no creo que deberia ir aca
	if(x + (CHAR_WIDTH * size) > _syscall(_getScreenWidth)) {
		y+= CHAR_HEIGHT * size;
		x = 0;
	}
	 char * posOfChar = getCharPos(c);
	for(int j = 0; j < CHAR_HEIGHT ; j++) {
		for(int i = 0, k = 128; i < CHAR_WIDTH; i++, k/=2){
			if(k & posOfChar[j])
				_syscall(_writeBlock,i*size + x, j*size + y, color,size,size);
		}
	}
}

void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size){
	while(*string != 0){
		if(x + (CHAR_WIDTH * size) >= _syscall(_getScreenWidth)){
			x = 0;
			y+=(CHAR_HEIGHT+1) * size;
		}
		if(y + (CHAR_HEIGHT * size) >= _syscall(_getScreenHeight))
			return;
		writeCharWithBackground(*string,x,y,color,background,size);
		x += (CHAR_WIDTH + 1) * size;
		string++;
	}
}

void clearScreen() {
	struct RGB black={0,0,0};
	_syscall(_fillScreen,black);
}
