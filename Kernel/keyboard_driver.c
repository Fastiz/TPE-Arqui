#include <stdint.h>
#include <keyboard.h>

#define BUFFER_SIZE 255

char buffer[BUFFER_SIZE];
int next = 0;
int size = 0;

void keyboard_handler() {
	char key = getKey();
	if(size >= BUFFER_SIZE)
		next++;
	buffer[(next+size) % BUFFER_SIZE] = key;
	if(size < BUFFER_SIZE)
		size++;
}

char getNextChar() {
	if(size == 0)
		return 0;
	if(next >= BUFFER_SIZE)
		next = 0;
	size--;
	return buffer[next++];
}
