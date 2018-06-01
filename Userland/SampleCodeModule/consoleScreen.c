void writeBlock(uint64_t width, uint64_t height, struct RGB color, uint64_t size){
	for(int i = width; i < width+size; i++){
		for(int j = height; j < height+size; j++){
			writePixel(i, j, color);
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
}

void writeString(char* string, uint64_t x, uint64_t y, struct RGB color, uint64_t size){
	while(*string != 0){
		writeChar(*string, x, y, color, size);
		x += (charWidth + 1) * size;
		string++;
	}
}

void fillScreen(struct RGB color){
	for(int y = 0; y < getHeight(); y++) {
		for(int x = 0; x < getWidth(); x++)
			writePixel(x,y,color);
	}
}

void clearScreen() {
	struct RGB black={0,0,0};
	fillScreen(black);
}

void moveScreenUp(uint64_t size, uint64_t ammount, struct RGB background) {
	for(int y = charHeight * size * ammount; y < screen->height; y++) {
		for(int x = 0; x < screen->width; x++) {
			writePixel(x, y - (charHeight * size * ammount), readPixel(x,y));
			if(y >= screen->height - (charHeight * size * ammount))
				writePixel(x, y, background);
		}
	}
}

void backupScreen() {
	for(int y = 0; y < getHeight(); y++) {
		for(int x = 0; x < getWidth(); x++)
			backup[x][y] = readPixel(x,y);
	}
}

void restoreScreen() {
	for(int y = 0; y < getHeight(); y++) {
		for(int x = 0; x < getWidth(); x++)
			writePixel(x,y,backup[x][y]);
	}
}
