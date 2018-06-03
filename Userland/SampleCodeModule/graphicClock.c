#include "syscall.h"
#include "screenManager.h"
#include "font.h"

#define LINEPOSITION_START 0
#define LINE_START 0
#define numOfColors 5

int posX = 0;
int posY = 0;
int size = 3;
int currentColor = 0;

struct RGB clockBackground = {0,0,0};
struct RGB colors[] = {{255,0,0},{0,255,0},{0,0,255},{0,255,255},{255,255,255}};

void drawClock(){
    char c = _syscall(_read,0);
    clearScreen();
    while(c != 'l') {
        int hour = _syscall(_readTime, 2);
        int min = _syscall(_readTime, 1);
        int sec = _syscall(_readTime, 0);
        
        writeInt(hour, posX, posY, colors[currentColor],clockBackground, size);
        posX += ((charWidth+1) * size)*2;
        writeCharWithBackground(':', posX, posY, colors[currentColor],clockBackground,size);
        posX += ((charWidth+1) * size);
        writeInt(min, posX, posY, colors[currentColor], clockBackground,size);
        posX += ((charWidth+1) * size)*2;
        writeCharWithBackground(':', posX, posY, colors[currentColor],clockBackground,size);
        posX += ((charWidth+1) * size);
        writeInt(sec, posX, posY, colors[currentColor],clockBackground, size);

        posX = LINEPOSITION_START;
        char c = _syscall(_read,0);
    }
}