#define BUFFER_SIZE 1024

struct Buffer {
   char buffer[BUFFER_SIZE];
   int start;
   int size;
};

static struct Buffer std_buffers[3];

void setUpBuffers() {
	struct Buffer std_out = {.buffer = {0}, .start = 0, .size = 0};
	std_buffers[0] = std_out;
	struct Buffer std_in = {.buffer = {0}, .start = 0, .size = 0};
	std_buffers[1] = std_in;
	struct Buffer std_err = {.buffer = {0}, .start = 0, .size = 0};
	std_buffers[2] = std_err;

}
void clearBuffer(int index){
	if(index > 2)
		return;
	int i;
	for(i = 0; i < BUFFER_SIZE ; i++)
		std_buffers[index].buffer[i] = 0;
	std_buffers[index].start = 0;
	std_buffers[index].size = 0;
}
int writeCharBuffer(int index, char character) {
	if(index > 2)
		return -1;
	if(std_buffers[index].size >= BUFFER_SIZE)
		std_buffers[index].start++;
	//Si ya llego al limite de tamaño, el final del buffer se mueve al principio del arreglo.
	std_buffers[index].buffer[(std_buffers[index].start + std_buffers[index].size) % BUFFER_SIZE] = character;
	if(std_buffers[index].size < BUFFER_SIZE)
			std_buffers[index].size++;
	return 0;
}

int writeStrBuffer(int index, char * str) {
	if(index > 2)
		return -1;
	int i;
	for(i = 0; str[i] != 0; i++)
		writeCharBuffer(index,str[i]);
	return 0;
}

char readCharBuffer(int index){
  	if(index > 2)
		return -1;
	if(std_buffers[index].size == 0)
		return 0;
	//Si ya llego al limite de tamaño, el final del buffer se mueve al principio del arreglo.
	char character = std_buffers[index].buffer[std_buffers[index].start];
	std_buffers[index].buffer[std_buffers[index].start++] = 0;
	std_buffers[index].size--;
	if(std_buffers[index].start >= BUFFER_SIZE)
			std_buffers[index].start = 0;;
	return character;
}

int readStrBuffer(int index, char * str) {
	if(index > 2)
		return -1;
	int i;
	for(i = 0; str[i] != 0; i++)
		str[i]=readCharBuffer(index);
	return 0;
}

