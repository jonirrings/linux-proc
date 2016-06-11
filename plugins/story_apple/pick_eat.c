#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "pick_eat.h"

extern void *pick_thread(void *arg);
extern void *eat_thread(void *arg);

static void story_apple(int kid) {
	pthread_t p_tid;
	pthread_t *k_tid;

	int i;

	bask_t bask;
	bask.max_vol = 50;
	bask.count = 0;
	bask.open = 1;
	pthread_mutex_init(&bask.pe_mutex, NULL);
	pthread_cond_init(&bask.pe_cond, NULL);

	printf("A parent with %d children goes to pick apples.\n", kid);

	// thread -- parent pick apple
	pthread_create(&p_tid, NULL, pick_thread, &bask);

	// threads -- children eat apple
	k_tid = (pthread_t *)malloc(sizeof(pthread_t) * kid);
	for (i = 0; i < kid; ++i) {
		pthread_create(&k_tid[i], NULL, eat_thread, &bask);
	}

	// wait until all threads over
	pthread_join(p_tid, NULL);
	for (i = 0; i < kid; ++i) {
		pthread_join(k_tid[i], NULL);
	}

	free(k_tid);

	printf("They are back on the way home.\n");

	pthread_cond_destroy(&bask.pe_cond);
	pthread_mutex_destroy(&bask.pe_mutex);
}

void plug_task(void) {
	story_apple(2);
}

