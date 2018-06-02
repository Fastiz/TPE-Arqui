

#include <syscall.h>
#include <font.h>
#include <stdint.h>
#include <screenManager.h>




struct RGB background = {0,0,0};

void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t size){
	for(int i = width; i < width+size; i++){
		for(int j = height; j < height+size; j++){
			//writePixel(i, j, color);
			_syscall(3, i, j, color);
		}
	}
}

void writeChar(char c, uint64_t x, uint64_t y, struct RGB color, uint64_t size){
	if(c < 32 || c > 255) //falta ver el limite de c, no es 255 en esta fuente
		return;
	char * posOfChar = getCharPos(c);
	for(int j = 0; j < charHeight ; j++) {
		for(int i = 0, k = 128; i < charWidth; i++, k/=2){
			if(k & posOfChar[j])
				writeBlock(i*size + x, j*size + y, color,size);
		}
	}
    /*currentX+= size * charWidth;
    if(currentX >= getWidth()) {
        currentX = 0;
        currentY += charHeight * size;
    }*/

}

/*void setSize(char s) {
	offset = s;
}*/

/*void putChar(char c, struct RGB color) {
	writeChar(c, currentX,currentY, color, offset);
}*/

/*void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, uint64_t size){
	while(*string != 0){
		putChar(*string,color);
		x += (charWidth + 1) * size;
		string++;
	}
}*/

//solo imprime string
/*void printString(char * string, struct RGB color) {
	writeString(string,currentX,currentY, color,offset);
}*/

void fillScreen(struct RGB color){
	for(int y = 0; y < _syscall(_getScreenHeight); y++) {
		for(int x = 0; x < _syscall(_getScreenWidth); x++)
			_syscall(_writePixel, x, y, color);
	}
}

/*void clearScreen() {
	struct RGB black={0,0,0};
	fillScreen(black);
	currentX = 0;
	currentY = 0;
}*/

void moveScreenUp(int offset, struct RGB background) {
    int height = _syscall(_getScreenHeight);
    int width = _syscall(_getScreenWidth);
	for(int y = offset; y < height; y++) {
		for(int x = 0; x < width; x++) {
			struct RGB color={0,0,0};
			_syscall(_readPixel,x,y, &color);
			_syscall(_writePixel, x, y - offset, color);
			if(y >= height - offset)
				_syscall(_writePixel, x, y, background);
		}
	}
}
