#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "option.h"

static void opt_set_default(opt_t *opt) {
	if (!opt) {
		return ;
	}

	memset(opt, 0, sizeof(opt_t));
}

static char *field(char **str) {
	char *f = *str;
	char *p;

	// field pos
	while (isspace(*f)) {
		f++;
	}
	if (*f == '\0') { // empty line
		return NULL;
	}

	// field end
	p = f + 1;
	while (*p && !isspace(*p)) {
		p++;
	}
	if (*p == '\0') {
		*str = p;
	} else {
		*p = '\0';
		*str = p + 1;
	}

	return f;
}

static int opt_plug_parse(char *line, opt_t *opt) {
	char *f;
	opt_plug_t *plug;

	if (!line || !opt) {
		return -1;
	}

	// file name
	f = field(&line);
	if (!f) {
		return 1;
	}

	plug = (opt_plug_t *)malloc(sizeof(opt_plug_t));
	strcpy(plug->file, f);
	plug->interval = 0;
	plug->next = NULL;

	// interval
	f = field(&line);
	if (f) {
		plug->interval = atoi(f);
	}

	// add to plug chain
	plug->next = opt->plug_list;
	opt->plug_list = plug;

	return 0;
}

static int opt_line_parse(char *line, opt_t *opt) {
	char *f;

	if (!line || !opt) {
		return -1;
	}

	// field
	f = field(&line);
	if (!f) {
		return 1;
	}

	// plugin option
	if (!strcmp(f, "plugin")) {
		opt_plug_parse(line, opt);
	}

	return 0;
}

opt_t *opt_load(const char *file) {
	opt_t *opt;

	FILE *pf;
	char line[MAX_LINE];

	// default options
	opt = (opt_t *)malloc(sizeof(opt_t));
	opt_set_default(opt);

	// read from file
	pf = fopen(file, "r");
	if (!pf) {
		return opt;
	}

	// read a line
	while (fgets(line, MAX_LINE, pf)) {
		// parse the option line
		opt_line_parse(line, opt);
	}

	fclose(pf);

	return opt;
}

void opt_clear(opt_t **opt) {
	void *p;

	if (!opt || !*opt) {
		return ;
	}

	// clear plug chain
	while ((*opt)->plug_list) {
		p = (*opt)->plug_list;
		(*opt)->plug_list = (*opt)->plug_list->next;
		free(p);
	}

	// clear opt
	free(*opt);

	*opt = NULL;
}

