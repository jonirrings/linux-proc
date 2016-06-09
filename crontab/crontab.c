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
	task_t *rear;

	// lock
	pthread_mutex_t mutex;
} task_tab = {
	NULL, NULL, PTHREAD_MUTEX_INITIALIZER
};

int task_add(void (*t)(void), unsigned int interval) {
	if (!t) {
		return -1;
	}

	task_t *task = (task_t *)malloc(sizeof(task_t));
	if (!task) {
		return -1;
	}

	memset(task, 0, sizeof(task_t));
	task->t_run = t;
	task->interval = interval;

	// add task to task_table
	pthread_mutex_lock(&task_tab.mutex);

	if (!task_tab.rear) { // no task
		task_tab.head = task;
		task_tab.rear = task;
	} else {
		task_tab.rear->next = task;
		task_tab.rear = task;
	}

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

	task_tab.rear = NULL;

	pthread_mutex_unlock(&task_tab.mutex);
}

static void task_run(void (*t)(void)) {
	(*t)();
}

static int task_check(const task_t *task, time_t tc) {
	return (tc - task->fore_run >= task->interval);
}

void task_cron() {
	time_t tc;

	task_t **p;
	task_t *cur;

	while (1) {
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

		pthread_mutex_lock(&task_tab.mutex);

		sleep(1);
	}
}

