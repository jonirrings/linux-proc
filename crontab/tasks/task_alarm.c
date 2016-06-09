#include <stdio.h>
#include <time.h>

static void print_time() {
	char buf[64];

	time_t t;
	struct tm *tmp;

	// locale time
	t = time(NULL);
	tmp = localtime(&t);

	// formatted time string
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tmp);

	printf("%s\n", buf);
}

void t_alarm() {
	// only print current time here
	print_time();
}

