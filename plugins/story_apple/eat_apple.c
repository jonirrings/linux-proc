#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "pick_eat.h"

/**
 * The child as a foodie is busy with the 
 * apple in the hand, with no time to care 
 * about the surrounds.
**/

static void job_eat(bask_t *bask, int kid) {
	int n_time = 3000;
	int n_apple = 0;

	if (!bask || !bask->open) {
		return ;
	}

	pthread_mutex_lock(&bask->pe_mutex);

	if (bask->open && !bask->count) { // no apples
		pthread_cond_wait(&bask->pe_cond, &bask->pe_mutex);
	}

	// pick an apple
	if (bask->open) {
		n_apple = 1;
		bask->count--;

		printf("[K%08lX]: Eat an apple. (%d/%d)\n", 
				kid, bask->count, bask->max_vol);
	}

	pthread_mutex_unlock(&bask->pe_mutex);

	// eat apple
	usleep(n_time * 1000);
}

void *eat_thread(void *arg) {
	bask_t *bask = (bask_t *)arg;

	int kid = (int)pthread_self();

	while (bask->open) {
		job_eat(bask, kid);
	}

	return NULL;
}

