#include "cron_task.h"

extern void t_alarm();

int main(int argc, char *argv[]) {
	task_add(t_alarm, 10);
	task_cron();

	return 0;
}

