#ifndef _QPT_HEADER_CRONTAB_TASK_H_
#define _QPT_HEADER_CRONTAB_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

typedef struct task {
	// task routine
	void (*t_run)(void);

	// timer
	unsigned int interval;
	time_t fore_run;

	// task chain
	struct task *next;
} task_t;

extern int task_add(void (*t)(void), unsigned int interval);
extern void task_clear();

extern void cron_start();
extern void cron_stop();

#ifdef __cplusplus
}
#endif

#endif // cron_task.h
