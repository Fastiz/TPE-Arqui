#include "screenManager.h"
#include "syscall.h"
#include "console.h"
#include "stdio.h"
#include "commandDispatcher.h"
#include "font.h"

#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 0
#define MAX_LINE_POSITION (windowWidth-(HORIZONTAL_MARGIN*(CHAR_WIDTH + 1)))

char buffer[20000];
int bufferIndex =0;

static const char* consoleName = "Consola\\::";

static const struct RGB consoleBackground = {0,0,0};
static const struct RGB consoleColor = {50,50,255};
static const struct RGB STDOUTColor = {255, 255, 255};
static const struct RGB STDINColor = {255, 255, 255};
static const struct RGB STDERRColor = {255, 50, 50};

int windowWidth;
int windowHeight;
int letterSize = 1;
int line=VERTICAL_MARGIN, linePosition=HORIZONTAL_MARGIN;

void console(){
  init();
  consoleLoop();
}


void init(){
  windowWidth = _syscall(_getScreenWidth);
  windowHeight = _syscall(_getScreenHeight);
  _syscall(_fillScreen,consoleBackground);
  printf("Welcome to MikeOS. To get started, type man to check the different programs.");
}

void consoleLoop(){
  stdout();
  stderr();
  while(1){
    stdin();
    stdout();
    stderr();
  }
}


void checkSpace(){
  if((linePosition + 1) * (CHAR_WIDTH + 1) * letterSize > MAX_LINE_POSITION)
    newLine();
  else if(line*letterSize*CHAR_HEIGHT >= windowHeight-VERTICAL_MARGIN*CHAR_HEIGHT*letterSize){
    _syscall(_movePixelsUp, letterSize*CHAR_HEIGHT, consoleBackground);
    line--;
  }
}

void stdin(){
  bufferIndex=0;
  char * text = consoleName;
  while(*text){
    writeChar(*text, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColor, letterSize);
    linePosition++;
    text++;
  }
  char c;
  while((c = _syscall(_read, 0)) != '\n'){
    if(c==8){
      if(bufferIndex!=0){
        if(linePosition <= HORIZONTAL_MARGIN){
          line--;
          linePosition=(MAX_LINE_POSITION / ((CHAR_WIDTH + 1) * letterSize)) - 1;
        }else
          linePosition--;
        
        bufferIndex--;

        	/* LE PUSE  buffer[bufferIndex] = 0; PORQUE SI NO CUANDO ESCRIBIS, DESPUES BORRAS Y ESCRIBIS UN COMANDO EL BUFFER NO ESCRIBE UN 0 DONDE BORRASTE,
	      ENTONCES NUNCA ENCUENTRA EL COMANDO, PORQUE EL STRING NO TIENE UN 0 AL FINAL (cuando los compara). OTRA OPCION ES
	      CAMBIAR EL && POR UN || EN LA QUE COMPARA STRINGS*/
        buffer[bufferIndex] = 0;
        _syscall(_writeBlock,(linePosition)*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleBackground, (CHAR_WIDTH + 1)*letterSize, CHAR_HEIGHT*letterSize);
      }
    }else if(c){
      checkSpace();
      buffer[bufferIndex++] = c;
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, STDINColor, letterSize);
      linePosition++;
    }
  }
  newLine();
  commandDispatcher(buffer);
  int i;
  for(i = 0; i < bufferIndex; i++)
    buffer[i] = 0;
  bufferIndex = 0;
}

void stdout(){
  int flag=0;
  char c;
  while(c=_syscall(_read, 1)){
    flag=1;
    if(c == '\n'){
      newLine();
    }else{
      checkSpace();
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, STDOUTColor, letterSize);
      linePosition++;
    }
  }
  if(flag)
    newLine();
}

void stderr(){
  int flag;
  char c;
  while(c=_syscall(_read, 2)){
    flag=1;
    if(c == '\n'){
      newLine();
    }else{
      checkSpace();
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, STDERRColor, letterSize);
      linePosition++;
    }
  }
  if(flag)
    newLine();
}

void resetConsole(){
  _syscall(_fillScreen, consoleBackground);
  linePosition = HORIZONTAL_MARGIN;
  line = VERTICAL_MARGIN;
}

void newLine(){
  line++;
  linePosition = HORIZONTAL_MARGIN;
  checkSpace();
}

