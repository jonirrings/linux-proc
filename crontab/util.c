#include <stdio.h>
#include <ctype.h>

char *trim(char *str) {
	char *left, *right;
	char *p;

	if (!str) {
		return NULL;
	}

	// first valid chars
	left = str;
	while (isspace(*left)) {
		left++;
	}
	if (*left == '\0') { // end
		*str = '\0';
		return str;
	}

	// last valid chars
	right = left;
	p = right + 1;
	while (*p) {
		if (!isspace(*p)) {
			right = p;
		}
		p++;
	}

	// copy
	p = str;
	while (left <= right) {
		*p++ = *left++;
	}
	*p = '\0';

	return str;
}

