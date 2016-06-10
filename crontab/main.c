#include "cron_task.h"

#include <stdio.h>
#include <unistd.h>

extern void t_alarm();
extern void t_cfib();

int main(int argc, char *argv[]) {
	// task 1
	printf("Add alarm task (1).\n");
	task_add(t_alarm, 5);

	cron_start();

	sleep(2);
	// task 2
	printf("Add cfib task (2).\n");
	task_add(t_cfib, 1);

	sleep(5);
	printf("Add alarm task (3).\n");
	task_add(t_alarm, 0);

	sleep(20);

	cron_stop();

	task_clear();

	printf("Crontab is over.\n");

	return 0;
}

