char * v = (char*)0xB8000;

void write(char * text, int pos, char format){ 
  int i=0;
  v+=pos*2;
  while(text[i/2]){
    v[i] = text[i/2];
    v[i+1] = format;
    i+=2;
  }
}
