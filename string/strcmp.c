#include <string.h>

int strcmp(const char *s1, const char *s2) {
	size_t len = 0;
	while(s1[len]&&s2[len++])
		if (s1[len]-s2[len]) return s1[len]-s2[len];
	return 0;
}
