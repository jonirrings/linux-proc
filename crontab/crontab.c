#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include "cron_task.h"

static struct {
	// task chain
	task_t *head;

	// lock
	pthread_mutex_t mutex;
} task_tab = {
	NULL, PTHREAD_MUTEX_INITIALIZER
};

static struct {
	int n_thread;

	pthread_mutex_t mutex;
	pthread_cond_t  cond;
} th_task = {
	0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};

// only one cron thread can run at a time
static struct {
	pthread_t tid;

	// thread status, is running
	int s_run;
	// command word, stop command
	int cw_stop;
} th_cron = {
	0, 0, 1
};

int task_add(void (*t)(void), unsigned int interval) {
	task_t *task;
	task_t **p;

	if (!t) {
		return -1;
	}

	task = (task_t *)malloc(sizeof(task_t));
	if (!task) {
		return -1;
	}

	memset(task, 0, sizeof(task_t));
	task->t_run = t;
	task->interval = interval;

	// add task to task_table
	pthread_mutex_lock(&task_tab.mutex);

	p = &task_tab.head;
	while (*p) {
		p = &(*p)->next;
	}
	*p = task;

	pthread_mutex_unlock(&task_tab.mutex);

	return 0;
}

void task_clear() {
	task_t **p;
	task_t *cur;

	pthread_mutex_lock(&task_tab.mutex);

	// clear all tasks
	p = &task_tab.head;
	while (*p) {
		cur = *p;
		*p = (*p)->next;
		free(cur);
	}

	pthread_mutex_unlock(&task_tab.mutex);
}

static void *task_thread(void *pf) {
	void (*t)(void) = (void (*)(void))pf;

	// Remark: tasks may run on threads with a same id 
	// as the previous thread is over and its id can 
	// be used again.
	printf("Task 0x%lX runs on Thread 0x%lX\n", 
			(unsigned long)t, (unsigned long)pthread_self());

	(*t)();

	// thread comes to the end
	pthread_mutex_lock(&th_task.mutex);
	th_task.n_thread--;
	if (!th_task.n_thread) { // no task threads
		pthread_cond_signal(&th_task.cond);
	}
	pthread_mutex_unlock(&th_task.mutex);

	return NULL;
}

static void task_run(void (*t)(void)) {
	pthread_t tid;

	// create a new thread for this task
	pthread_mutex_lock(&th_task.mutex);
	pthread_create(&tid, NULL, task_thread, t);
	pthread_detach(tid);
	th_task.n_thread++;
	pthread_mutex_unlock(&th_task.mutex);
}

static int task_check(const task_t *task, time_t tc) {
	return (tc - task->fore_run >= task->interval);
}

static void *task_cron_thread(void *arg) {
	time_t tc;

	task_t **p;
	task_t *cur;

	while (!th_cron.cw_stop) {
		// current time
		tc = time(NULL);

		pthread_mutex_lock(&task_tab.mutex);

		p = &task_tab.head;
		while (*p) {
			if (task_check(*p, tc)) {
				task_run((*p)->t_run);
				(*p)->fore_run = tc;
			}

			if (!(*p)->interval) { // only run once
				cur = *p;
				*p = (*p)->next;
				free(cur);
			} else {
				p = &(*p)->next;
			}
		}

		pthread_mutex_unlock(&task_tab.mutex);

		sleep(1);
	}

	return NULL;
}

void cron_start() {
	// a cron thread already runs
	if (th_cron.s_run) {
		return ;
	}
	
	th_cron.cw_stop = 0;
	pthread_create(&th_cron.tid, NULL, task_cron_thread, NULL);
	th_cron.s_run = 1;
}

void cron_stop() {
	th_cron.cw_stop = 1;

	// wait until cron thread over
	pthread_join(th_cron.tid, NULL);

	// wait until task threads over
	pthread_mutex_lock(&th_task.mutex);
	if (th_task.n_thread) {
		pthread_cond_wait(&th_task.cond, &th_task.mutex);
	}
	pthread_mutex_unlock(&th_task.mutex);

	// make sure all task threads dead
	sleep(1);

	th_cron.s_run = 0;
}

