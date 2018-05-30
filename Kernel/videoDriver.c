#include "lib.h"
#include "font.h"

struct vesa_mode {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

	struct vesa_mode * screen = (struct vesa_mode*)0x0000000000005C00;
	struct RGB backup[1020][1000];

	int getWidth(){
		return screen->width;
	}

	int getHeight(){
		return screen->height;
	}

	struct RGB readPixel(int width, int height) {
		struct RGB color = {0,0,0};
		if(!(width > screen->width || height > screen->height || width < 0 || height < 0)) {
			int pixelIndex = width + height*(screen->width);
		    char * pixelPos = (char*)(screen->framebuffer + pixelIndex*(screen->bpp/8));
		    color.red=*(pixelPos+2);
		    color.green=*(pixelPos+1);
		    color.blue=*(pixelPos);
	    }
	    return color;
	}

	void writePixel(int width, int height, struct RGB color){
		if(width > screen->width || height > screen->height || width < 0 || height < 0)
			return;

	    int pixelIndex = width + height*(screen->width);
	    char * pixelPos = (char*)(screen->framebuffer + pixelIndex*(screen->bpp/8));
		*(pixelPos+2) = color.red;
		*(pixelPos+1) = color.green;
		*(pixelPos) = color.blue;
	}

	void writeBlock(int width, int height, struct RGB color, int size){
		for(int i = width; i < width+size; i++){
			for(int j = height; j < height+size; j++){
				writePixel(i, j, color);
			}
		}
	}

	void writeChar(char c, int x, int y, struct RGB color, int size){
	 	if(c < 32 || c > 255)
	 		return;
	 	char * posOfChar = getCharPos(c);
		for(int j = 0; j < charHeight ; j++) {
			for(int i = 0, k = 128; i < charWidth; i++, k/=2){
				if(k & posOfChar[j])
					writeBlock(i*size + x, j*size + y, color,size);
		 	}
		}
	}

	void writeString(char* string, int x, int y, struct RGB color, int size){
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