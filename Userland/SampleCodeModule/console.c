#include "screenManager.h"
#include "syscall.h"
#include "console.h"


#define ROW_HEIGHT 16
#define LETTER_WIDTH 9
#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 2

static const char buffer[200];

//static const int windowWidth = getVideoDriverWidth();
//static const int windowHeight = getVideoDriverHeight();
int line=0, linePosition=0;

void console(){
  consoleLoop();
}

//void newLine(){}


void consoleLoop(){
  struct RGB color = {0,0,255};
  while(1){
    char c = readStdin();
    if(c){
      writeChar(c, 50, 50, color, 2);
    }
  }
}

char readStdin(){
  return _syscall(_read, 0);
  //return 'c';
}
