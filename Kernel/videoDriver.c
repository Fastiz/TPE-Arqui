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

	uint64_t getWidth(uint64_t trash1, uint64_t trash2, uint64_t trash3, uint64_t trash4){
		return screen->width;
	}

	uint64_t getHeight(uint64_t trash1, uint64_t trash2, uint64_t trash3, uint64_t trash4){
		return screen->height;
	}

	uint64_t readPixel(uint64_t width, uint64_t height, uint64_t trash1, uint64_t trash2) {
		struct RGB color = {0,0,0};
		if(!(width > screen->width || height > screen->height || width < 0 || height < 0)) {
			int pixelIndex = width + height*(screen->width);
		    char * pixelPos = (char*)(screen->framebuffer + pixelIndex*(screen->bpp/8));
		    color.red=*(pixelPos+2);
		    color.green=*(pixelPos+1);
		    color.blue=*(pixelPos);
	    }
	    return (uint64_t)color;
	}

	uint64_t writePixel(uint64_t width, uint64_t height, uint64_t color, uint64_t trash1){
		struct RGB colorStructure = (struct RGB) color;
		if(width > screen->width || height > screen->height || width < 0 || height < 0)
			return;

	    int pixelIndex = width + height*(screen->width);
	    char * pixelPos = (char*)(screen->framebuffer + pixelIndex*(screen->bpp/8));
		*(pixelPos+2) = colorStructure.red;
		*(pixelPos+1) = colorStructure.green;
		*(pixelPos) = colorStructure.blue;
	}
