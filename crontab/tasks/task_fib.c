#include <stdio.h>

static int a = 0, b = 1;

// continous fibonacci
void t_cfib() {
	int f = a + b;
	printf("Fib: %d + %d = %d\n", a, b, f);

	if (f >= 0x0F000000) {
		a = 0, b = 1;
	} else {
		a = b, b = f;
	}
}

