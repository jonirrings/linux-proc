#include <stdio.h>

static int a = 0, b = 1;

// continous fibonacci
void t_cfib() {
	int f = a + b;
	a = b, b = f;

	printf("%d\n", f);
}

