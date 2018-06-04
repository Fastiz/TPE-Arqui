

#include <syscall.h>
#include <font.h>
#include <stdint.h>
#include <screenManager.h>




struct RGB background = {0,0,0};

void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t sizeX,uint64_t sizeY){
	for(int i = width; i < width+sizeX; i++){
		for(int j = height; j < height+sizeY; j++){
			//writePixel(i, j, color);
			_syscall(3, i, j, color);
		}
	}
}

void writeCharWithBackground(char c, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size){
	if(c < 32 || c > 255) //falta ver el limite de c, no es 255 en esta fuente
		return;

	char * posOfChar = getCharPos(c);
	for(int j = 0; j < charHeight ; j++) {
		for(int i = 0, k = 128; i < charWidth; i++, k/=2){
			if(k & posOfChar[j])
				writeBlock(i*size + x, j*size + y, color,size,size);
			else
				writeBlock(i*size + x, j*size + y, background,size,size);
		}
	}
}

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size){
	if(c < 32 || c > 255) //falta ver el limite de c, no es 255 en esta fuente
		return;
	//no creo que deberia ir aca
	if(x + (charWidth * size) > _syscall(_getScreenWidth)) {
		y+= charHeight * size;
		x = 0;
	}
	char * posOfChar = getCharPos(c);
	for(int j = 0; j < charHeight ; j++) {
		for(int i = 0, k = 128; i < charWidth; i++, k/=2){
			if(k & posOfChar[j])
				writeBlock(i*size + x, j*size + y, color,size,size);
		}
	}
}

void writeIntR(uint64_t num, uint64_t x, uint64_t y, struct RGB color,struct RGB background, uint64_t size){
	if(num == 0)
		return;
	writeIntR(num /10, x - (charWidth * size), y, color,background, size);
	writeCharWithBackground(num %10 + '0', x, y, color,background,size);
}

void writeInt(uint64_t num, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size){
	if(num == 0){
		writeCharWithBackground('0', x,y,color,background,size);
		return;
	}
	if(num < 0) {
		writeCharWithBackground('-',x,y,color,background,size);
		x += charHeight * size;
		num = -num;
	}
	int aux = num;
	int i = 0;
	while(aux != 0) {
		aux /= 10;
		i++;
	}
	writeIntR(num, x + ((i-1)*charWidth*size), y, color,background, size);
}



/*void setSize(char s) {
	offset = s;
}*/

/*void putChar(char c, struct RGB color) {
	writeChar(c, currentX,currentY, color, offset);
}*/

void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, struct RGB background, uint64_t size){
	while(*string != 0){
		writeCharWithBackground(*string,x,y,color,background,size);
		x += (charWidth + 1) * size;
		string++;
	}
}

//solo imprime string
/*void printString(char * string, struct RGB color) {
	writeString(string,currentX,currentY, color,offset);
}*/

void clearScreen() {
	struct RGB black={0,0,0};
	_syscall(_fillScreen,black);
}
