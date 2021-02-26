#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n) {
	size_t len = 0;
	while(len<n&&s1[len]&&s2[len++])
		if (s1[len]-s2[len]) return s1[len]-s2[len];
	return 0;
}
