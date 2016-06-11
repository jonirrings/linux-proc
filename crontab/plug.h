#ifndef _QPT_HEADER_PLUGIN_MODULE_H_
#define _QPT_HEADER_PLUGIN_MODULE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct plug {
	// handle of a shared object
	void *handle;

	// address of task function
	void (*entry)(void);

	struct plug *next;
} plug_t;

extern plug_t *plug_load(const char *file);
extern void plug_unload(plug_t **plug);

extern void plug_task_add(plug_t *plug, unsigned int interval);
extern void plug_clear();

#ifdef __cplusplus
}
#endif

#endif // plug.h
