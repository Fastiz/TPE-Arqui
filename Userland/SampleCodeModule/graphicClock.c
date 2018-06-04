#include "syscall.h"
#include "screenManager.h"
#include "font.h"
#include "stdlib.h"

#define NUM_OF_COLORS 6
#define MARGIN 10
#define LARGEST_MESSAGE 22 

int posX = MARGIN;
int posY = MARGIN;
int size = 20;
int helpStartRow;
int helpLetterSize = 2;

int numbersColor = 1;
int backgroundColorIndex = 0;
struct RGB helpColor = {190,180,220};  
struct RGB colors[] = {{0,0,0},{255,0,0},{0,255,0},{0,0,255},{0,255,255},{255,255,0}};

void writeSettings() {
    if((MARGIN * 2) + ((charWidth+1)*helpLetterSize*(LARGEST_MESSAGE-1)) + (charWidth*size) >= _syscall(_getScreenWidth))
        helpLetterSize = 1;
    _syscall(_fillScreen, colors[backgroundColorIndex]);
    writeString("[C]hange numbers color",MARGIN,helpStartRow,helpColor,colors[backgroundColorIndex], helpLetterSize);
    writeString("[R]educe size",MARGIN,helpStartRow+(helpLetterSize*(charHeight +1)),helpColor,colors[backgroundColorIndex], helpLetterSize);
    writeString("[I]ncrement size",MARGIN,helpStartRow+(2*(helpLetterSize*(charHeight +1))),helpColor,colors[backgroundColorIndex], helpLetterSize);
    writeString("[B]ackground color",MARGIN,helpStartRow+(3*(helpLetterSize*(charHeight +1))),helpColor,colors[backgroundColorIndex], helpLetterSize);
    writeString("[Q]uit clock",MARGIN,helpStartRow+(4*(helpLetterSize*(charHeight +1))),helpColor,colors[backgroundColorIndex], helpLetterSize);
}

void drawClock(){

    _syscall(_backupScreen);
    char c;
    while((MARGIN * 2) + ((charWidth+1)*size*7) + (charWidth*size) >= _syscall(_getScreenWidth))
        size--;
    
    helpStartRow = _syscall(_getScreenHeight) - MARGIN - ((charHeight + 1) * helpLetterSize * 5);
    while(helpStartRow < MARGIN + (charHeight) * size)
        size--;

    int maxSize = size;
    
    writeSettings();
    
    while((c = _syscall(_read, 0)) != 'q') {
        posX = MARGIN;
        char clockTime[9] = {0};
        clockString(clockTime);

        switch(c) {
            case 'i':
                if(size != maxSize) {
                    size++;
                    writeBlock(0,0,colors[backgroundColorIndex],(MARGIN * 2) + ((charWidth+1)*maxSize*7) + (charWidth*maxSize), (charHeight * maxSize) + MARGIN);
                }
                break;

            case 'r': 
                if(size - 1 != 0){
                    size--;
                    writeBlock(0,0,colors[backgroundColorIndex],(MARGIN * 2) + ((charWidth+1)*maxSize*7) + (charWidth*maxSize), (charHeight * maxSize) + MARGIN);
                }
                break;
            
            case 'c': 
                numbersColor++;
                if(numbersColor == backgroundColorIndex)
                    numbersColor++;
                if(numbersColor == NUM_OF_COLORS) {
                    numbersColor = 0;
                    if(numbersColor == backgroundColorIndex)
                        numbersColor++;
                }
                break;
            
            case 'b': {
                int oldIndex = backgroundColorIndex;
                backgroundColorIndex++;
                if(numbersColor == backgroundColorIndex)
                    backgroundColorIndex++;
                if(backgroundColorIndex == NUM_OF_COLORS) {
                    backgroundColorIndex = 0;
                    if(numbersColor == backgroundColorIndex)
                        backgroundColorIndex++;
                }
                _syscall(_replaceColor, colors[oldIndex], colors[backgroundColorIndex]);
                break;
            }
        }

        for(int i = 0; i < 8; i++) {
            writeCharWithBackground(clockTime[i], posX,posY,colors[numbersColor], colors[backgroundColorIndex], size);
            posX += (charWidth + 1) * size;
        }
    }
    _syscall(_restoreScreen);
}