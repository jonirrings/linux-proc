#include <stdlib.h>
#include <dlfcn.h>

#include "plug.h"
#include "crontab.h"

#define PLUG_TASK_ENTRY "plug_task"

typedef plug_t *plug_list;
static plug_list pl = NULL;

plug_t *plug_load(const char *file) {
	void *hplug;
	void *pf_task;
	plug_t *plug;

	// load so
	hplug = dlopen(file, RTLD_LAZY);
	if (!hplug) {
		return NULL;
	}

	// find task entry
	pf_task = dlsym(hplug, PLUG_TASK_ENTRY);
	if (!pf_task) {
		dlclose(hplug);
		return NULL;
	}
	
	// new plug
	plug = (plug_t *)malloc(sizeof(plug_t));
	plug->handle = hplug;
	plug->entry = (void (*)(void))pf_task;
	plug->next = NULL;

	return plug;
}

void plug_unload(plug_t **plug) {
	if (*plug) {
		dlclose((*plug)->handle);
		free(*plug);
		*plug = NULL;
	}
}

void plug_task_add(plug_t *plug, unsigned int interval) {
	if (!plug) {
		return ;
	}

	// add task
	task_add(plug->entry, interval);

	// add plugin into list
	plug->next = pl;
	pl = plug;
}

void plug_clear() {
	plug_t *cur;

	while (pl) {
		cur = pl;
		pl = pl->next;

		plug_unload(&cur);
	}
}

