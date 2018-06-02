#include "screenManager.h"
#include "syscall.h"
#include "console.h"


#define ROW_HEIGHT 16
#define LETTER_WIDTH 9
#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 2

#define LETTER_SPACE 10

char buffer[200];
int bufferIndex =0;

static const char* consoleName = "Consola\\::";

static const struct RGB consoleBackground = {100,100,100};
static const struct RGB consoleColor = {0,0,255};
static const struct RGB STDOUTColor = {255, 255, 255};
static const struct RGB STDINColor = {255, 255, 255};
static const struct RGB STDERRColor = {255, 0, 0};

//static const int windowWidth = getVideoDriverWidth();
//static const int windowHeight = getVideoDriverHeight();
int letterSize = 1;
int line=VERTICAL_MARGIN, linePosition=HORIZONTAL_MARGIN;

void console(){
  init();
  consoleLoop();
}

//void newLine(){}

void init(){
  fillScreen(consoleBackground);
}

void consoleLoop(){
  while(1){
    readStdin();
  }

}

void readStdin(){

  char * text = consoleName;
  while(*text){
    writeChar(*text, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, consoleColor, letterSize);
    linePosition++;
    text++;
  }
  char c;
  while((c = _syscall(_read, 0)) != '\n'){
    if(c==8){
      if(bufferIndex!=0){
        writeChar(buffer[--bufferIndex], (--linePosition)*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, consoleBackground, letterSize);
      }
    }else if(c){
      buffer[bufferIndex++] = c;
      writeChar(c, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, STDINColor, letterSize);
      linePosition++;
    }
  }
  newLine();
  bufferIndex=0;
}

void newLine(){
  line++;
  linePosition = HORIZONTAL_MARGIN;
}
