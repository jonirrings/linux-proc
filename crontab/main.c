#include <stdio.h>
#include <unistd.h>

#include "crontab.h"
#include "plug.h"

extern void t_alarm();
extern void t_cfib();

int main(int argc, char *argv[]) {
	int n_task = 0;
	plug_t *plug = NULL;

	printf("Add alarm task (%d).\n", n_task++);
	task_add(t_alarm, 0);

	cron_start();

	plug = plug_load("../plugins/alien_ton.so");
	if (plug) {
		printf("Add alien_ton task (%d).\n", n_task++);
		plug_task_add(plug, 4);
	}

	sleep(2);
	printf("Add cfib task (%d).\n", n_task++);
	task_add(t_cfib, 1);

	sleep(20);

	printf("Add alarm task (%d).\n", n_task++);
	task_add(t_alarm, 0);
	sleep(1);

	cron_stop();

	task_clear();

	plug_clear();

	printf("Crontab is over.\n");

	return 0;
}

