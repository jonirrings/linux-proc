#ifndef _QPT_HEADER_PICK_AND_EAT_APPLE_H_
#define _QPT_HEADER_PICK_AND_EAT_APPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

typedef struct apple_basket {
	// apple count
	int count;
	// max volume
	int max_vol;

	// primitive for pick and eat task
	pthread_mutex_t pe_mutex;
	pthread_cond_t pe_cond;

	// close basket if it's full
	volatile int open;
} bask_t;

#ifdef __cplusplus
}
#endif

#endif // pick_eat.h
