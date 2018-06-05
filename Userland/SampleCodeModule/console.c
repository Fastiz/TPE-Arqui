#include "screenManager.h"
#include "syscall.h"
#include "console.h"
#include "stdio.h"
#include "commandDispatcher.h"
#include "font.h"

#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 0
#define MAX_LINE_POSITION (windowWidth-(HORIZONTAL_MARGIN*(CHAR_WIDTH)))
#define NUM_OF_COLORS 6
#define BLACK 0
#define WHITE 1
#define BLUE 2
#define RED 3
#define GREEN 4
#define YELLOW 5



char buffer[20000];
int bufferIndex =0;

static const char* consoleName = "Consola\\::";

static const struct RGB consoleColors[6] = {{0,0,0},{255,255,255},{50,50,255},{255, 50, 50},{50,255,50},{189,183,107}};
static int consoleBackgroundIndex = BLACK;
static int inOutIndex = WHITE;
static int errIndex = RED;
static int consoleIndex = BLUE;

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
  _syscall(_fillScreen,consoleColors[consoleBackgroundIndex]);
  printf("Welcome to MikeOS. To get started, type man to check the different programs.");
	printf("%d\n" "%d",_syscall(_getScreenWidth), _syscall(_getScreenHeight));
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
    _syscall(_movePixelsUp, letterSize*CHAR_HEIGHT, consoleColors[consoleBackgroundIndex]);
    line--;
  }
}

void stdin(){
  bufferIndex=0;
  char * text = consoleName;
  while(*text){
    writeChar(*text, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColors[consoleIndex], letterSize);
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
        buffer[bufferIndex] = 0;
        _syscall(_writeBlock,(linePosition)*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColors[consoleBackgroundIndex], (CHAR_WIDTH + 1)*letterSize, CHAR_HEIGHT*letterSize);
      }
    }else if(c){
      checkSpace();
      buffer[bufferIndex++] = c;
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColors[inOutIndex], letterSize);
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
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColors[inOutIndex], letterSize);
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
      writeChar(c, linePosition*letterSize*(CHAR_WIDTH + 1), line*letterSize*CHAR_HEIGHT, consoleColors[errIndex], letterSize);
      linePosition++;
    }
  }
  if(flag)
    newLine();
}

void resetConsole(){
  _syscall(_fillScreen, consoleColors[consoleBackgroundIndex]);
  linePosition = HORIZONTAL_MARGIN;
  line = VERTICAL_MARGIN;
}

void newLine(){
  line++;
  linePosition = HORIZONTAL_MARGIN;
  checkSpace();
}

void changeTheme(int type) {
  int c1 = inOutIndex;
  int c2 = consoleBackgroundIndex;
  int c3 = errIndex;
  int c4 = consoleIndex;

  switch(type) {
    case 1 : {
      int aux = c1;
      c1 = c2;
      c2 = aux;
      break;
    }
    case 2 : {
      int aux = c2;
      c2 = c3;
      c3 = aux;
      break;
    }
    case 3 : {
      int aux = c3;
      c3 = c4;
      c4 = aux;
      break;
    }
  }
  int oldIndex = c1;
  c1++;
  while(c1 == c2 || c1 == c3 || c1 == c4 || c1 >= NUM_OF_COLORS) {
    c1++;
    if(c1 >= NUM_OF_COLORS)
      c1 = 0;
  }

  switch(type) {
    case 0: {
      inOutIndex = c1;
      break;
    }
    case 1 : {
      consoleBackgroundIndex = c1;
      break;
    }
    case 2 : {
      errIndex = c1;
      break;
    }
    case 3 : {
      consoleIndex = c1;
      break;
    }
  }
  _syscall(_replaceColor, consoleColors[oldIndex], consoleColors[c1]);

}
