#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LEN_WORDS (64 - 1)

static void print_alien_ton() {
	char ws[MAX_LEN_WORDS + 1] = {0};

	char ch;
	int i, nw;

	srand(time(NULL));

	// total words
	nw = rand() % MAX_LEN_WORDS + 1;

	// generate words
	i = 0;
	while (i < nw) {
		ch = (char)(rand() % 128);
		if (isprint(ch)) {
			ws[i++] = ch;
		}
	}

	printf("Alien Words: %s\n", ws);
}

void plug_task(void) {
	print_alien_ton();
}

