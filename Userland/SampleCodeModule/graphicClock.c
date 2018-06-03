#include "syscall.h"
#include "screenManager.h"
#include "font.h"

#define NUM_OF_COLORS 5
#define MARGIN 10

int posX = MARGIN;
int posY = MARGIN;
int size = 15;
int currentColor = 0;
int helpStartRow;
int helpLetterSize = 2;
int backgroundColorIndex = -1;

struct RGB clockBackground = {0,0,0};
struct RGB colors[] = {{255,0,0},{0,255,0},{0,0,255},{0,255,255},{255,255,0}};

static int decToHex(int num) {
    int aux = 0;
    int mult1 = 1;
    int mult2 = 1;
    for(; num != 0; num/=10, mult1*=10, mult2*=16) {
        aux += (num %10) * mult1 * mult1 / mult2;
    }
    return aux;
}

void drawClock(){

    _syscall(_backupScreen);
    char c;
    while((MARGIN * 2) + ((charWidth+1)*size*8) >= _syscall(_getScreenWidth)) {
        size--;
    }
    int maxSize = size;
    helpStartRow = _syscall(_getScreenHeight) - MARGIN - ((charHeight + 1) * helpLetterSize * 4);
    
    clearScreen();
    while((c = _syscall(_read, 0)) != 'q') {
        posX = MARGIN;
        char clockTime[16] = {0};

        int secondsInt = _syscall(_readTime,0);
        int minutesInt =_syscall(_readTime,1);
        int hourInt =_syscall(_readTime,2);

        intToChar(secondsInt,16,clockTime + 6);
        intToChar(minutesInt,16,clockTime + 3);
        intToChar(hourInt,16,clockTime);

        if(hourInt < 10) {
           clockTime[1] = clockTime[0];
           clockTime[0] = '0';
        }
        if(minutesInt < 10){
            clockTime[4] = clockTime[3];
            clockTime[3] = '0';
        }
        if(secondsInt < 10) {
            clockTime[7] = clockTime[6];
            clockTime[6] = '0';
        }

        clockTime[2] = ':';
        clockTime[5] = ':';

        if( c == 'i') {
            if(size != maxSize) {
                size++;
                _syscall(_fillScreen, clockBackground);
            }
        }
        if(c == 'r') {
            if(size - 1 != 0){
                size--;
                _syscall(_fillScreen, clockBackground);
            }
        }
        if(c == 'c'){
            currentColor++;
            if(currentColor == NUM_OF_COLORS)
                currentColor = 0;
        }

        //esto era solo para probar el replace color, es puede hacer pero esta mal asi
        if(c == 'b') {
            if(backgroundColorIndex == -1) {
                backgroundColorIndex = 0;
                if(backgroundColorIndex == currentColor)
                    backgroundColorIndex++;
                struct RGB black = {0,0,0};
                _syscall(_replaceColor,black , colors[backgroundColorIndex]);
            }
            else {
                int oldIndex = backgroundColorIndex++;
                if(backgroundColorIndex == currentColor) 
                    backgroundColorIndex++;
                if(backgroundColorIndex >= NUM_OF_COLORS)
                    backgroundColorIndex = 0;
                _syscall(_replaceColor, colors[oldIndex], colors[backgroundColorIndex]);
                }
            clockBackground = colors[backgroundColorIndex];
        }

        writeString("[C]hange color",MARGIN,helpStartRow,colors[4],clockBackground, helpLetterSize);
        writeString("[R]educe size",MARGIN,helpStartRow+(helpLetterSize*(charHeight +1)),colors[4],clockBackground, helpLetterSize);
        writeString("[I]ncrement size",MARGIN,helpStartRow+(2*(helpLetterSize*(charHeight +1))),colors[4],clockBackground, helpLetterSize);
        writeString("[Q]uit clock",MARGIN,helpStartRow+(3*(helpLetterSize*(charHeight +1))),colors[4],clockBackground, helpLetterSize);

        int i = 0;
        while(i < 8) {
            writeCharWithBackground(clockTime[i], posX,posY,colors[currentColor], clockBackground, size);
            posX += (charWidth + 1) * size;
            i++;
        }
    }
    _syscall(_restoreScreen);
}