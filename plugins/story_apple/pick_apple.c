#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "pick_eat.h"

static void e_bird(int per) {
	int n_time = 1000;

	usleep(n_time * 1000);
	printf("[P%08lX]:\n"
			"A bird flies around the apple tree,\n"
			"with eyes staring on apples.\n"
			"It takes %d ms to scare it away.\n", 
			per, n_time);
}

static void e_wilddog(int per) {
	int n_time = 2500;

	usleep(n_time * 1000);
	printf("[P%08lX]:\n"
			"A wild dog runs fast towards here,\n"
			"whose barks make us crazy.\n"
			"Drive it away with %d ms.\n", 
			per, n_time);
}

static void e_neighbor(int per) {
	int n_time = 500;

	usleep(n_time * 1000);
	printf("[P%08lX]:\n"
			"An acquaintance walks past,\n"
			"saying hello to us.\n" 
			"It's polite to take %d ms to greet him.\n", 
			per, n_time);
}

static void e_break(int per) {
	int n_time = 2000;

	usleep(n_time * 1000);
	printf("[P%08lX]:\n"
			"Tired, and better to take a break with %d ms.\n", 
			per, n_time);
}

/**
 * The parent should pick apples on one hand, 
 * and also need to deal with special events, 
 * such as protecting children from wild dogs, 
 * on the other hand.
**/
static const struct {
	// events occur while picking apples
	void (*event)(int);

	// probability of this event occuring
	// and at a time only one event can occur
	int prob;
} event_tab[] = {
	{e_bird, 8}, 
	{e_wilddog, 5}, 
	{e_neighbor, 10}, 
	{e_break, 6}
};
static const int n_event = 
		sizeof(event_tab) / sizeof(event_tab[0]);

static void *gen_event() {
	void *ev = NULL;
	int i;
	int p, total;

	// used to gen random event
	srand(time(NULL));
	p = rand() % 100;

	// event based on probability
	total = 0;
	for (i = 0; i < n_event; ++i) {
		total += event_tab[i].prob;
		if (p < total) {
			ev = event_tab[i].event;
			break;
		}
	}

	return ev;
}

static void job_pick(bask_t *bask, int per) {
	int n_time = 500;

	// no basket or basket is full
	if (!bask || !bask->open) {
		return ;
	}

	// pick an apple
	usleep(n_time * 1000);

	pthread_mutex_lock(&bask->pe_mutex);

	bask->count++;
	printf("[P%08lX]: Pick an apple. (%d/%d)\n", 
			per, bask->count, bask->max_vol);

	// from 0 to 1
	if (1 == bask->count) {
		pthread_cond_signal(&bask->pe_cond);
	}

	// is full
	if (bask->count == bask->max_vol) { // is full
		// close basket
		bask->open = 0;
		printf("Basket is full and then close it.\n");

		// back home, wake all children
		pthread_cond_broadcast(&bask->pe_cond);
	}

	pthread_mutex_unlock(&bask->pe_mutex);
}

void *pick_thread(void *arg) {
	bask_t *bask = (bask_t *)arg;

	void (*do_event)(int) = NULL;
	int nt = 0;

	int per_id = (int)pthread_self();

	while (bask->open) {
		// random event
		do_event = (void (*)(int))gen_event();

		if (!do_event) { // no event
			job_pick(bask, per_id);
		} else {
			(*do_event)(per_id);
		}
	}

	return NULL;
}

