#ifndef _QPT_HEADER_OPTIONS_H_
#define _QPT_HEADER_OPTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LINE 256
#define MAX_PATH 256

typedef struct plugin_option {
	char file[MAX_PATH];
	int interval;

	struct plugin_option *next;
} opt_plug_t;

typedef struct option {
	// opt file only contains plugins
	opt_plug_t *plug_list;
} opt_t;

extern opt_t *opt_load(const char *file);
extern void opt_clear(opt_t **opt);

#ifdef __cplusplus
}
#endif

#endif // option.h
