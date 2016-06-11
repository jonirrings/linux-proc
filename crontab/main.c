#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "crontab.h"
#include "plug.h"
#include "option.h"

extern void t_alarm();
extern void t_cfib();

static void init_module() {
	opt_t *opt;
	opt_plug_t *tpg;

	plug_t *plug;

	// load options
	opt = opt_load("../etc/options");

	// init plugins
	tpg = opt->plug_list;
	while (tpg) {
		plug = plug_load(tpg->file);
		if (plug) {
			printf("Plugin %s loaded.\n", tpg->file);
			plug_task_add(plug, tpg->interval);
		}
		tpg = tpg->next;
	}

	opt_clear(&opt);
}

static void clear_proc() {
	task_clear();
	plug_clear();
}

static int proc_stop = 0;
static void sig_quit(int signo) {
	proc_stop = 1;
}

int main(int argc, char *argv[]) {
	signal(SIGINT, sig_quit);

	init_module();

	task_add(t_alarm, 1);
	cron_start();

	while (!proc_stop) {
		sleep(1);
	}

	cron_stop();

	clear_proc();

	printf("Crontab is over.\n");

	return 0;
}

