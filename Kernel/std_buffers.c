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
int writeBuffer(int index, char * str) {
	if(index > 2)
		return -1;
	struct Buffer selectedBuffer = std_buffers[index];
	int i;
	for(i = 0; str[i] != 0; i++){
		//Si ya llego al limite de tamaño, el final del buffer se mueve al principio del arreglo.
		if(selectedBuffer.size >= BUFFER_SIZE)
			selectedBuffer.start++;
		selectedBuffer.buffer[(selectedBuffer.start + selectedBuffer.size) % BUFFER_SIZE] = str[i];
		if(selectedBuffer.size < BUFFER_SIZE)
			selectedBuffer.size++;
	}
}
char * readBuffer(int index) {
	if(index > 2)
		return 0;
	char buffer_copy[BUFFER_SIZE];
	struct Buffer selectedBuffer = std_buffers[index];
	int i;
	char nextChar;
	for(i = 0 ; i < selectedBuffer.size ; i++){
		nextChar =  selectedBuffer.buffer[(selectedBuffer.start + i) % BUFFER_SIZE];
		buffer_copy[i] = nextChar;
		if(nextChar == 0)
			break;
	}
	return buffer_copy;
}