#include <stdlib.h>

int atoi (const char *str) {
	int sign = 1;
	const char *cstr = str;
	while(*cstr) {
		if (!isspace((int)*cstr))
			break;
		cstr++;
	}
	if (*cstr == '+') {
		cstr ++;
	} else if (*cstr == '-') {
		sign = -1;
		cstr ++;
	}
	const char* strbegin = cstr;
	while (*cstr >= '0' && *cstr <= '9')
	    cstr++;
	int multiplier = 1;
	int out = 0;
	while (cstr-- != strbegin) {
		if (out + ((*cstr-'0') * multiplier) < out)
			return INT_MAX;
		out += (*cstr-'0') * multiplier;
		multiplier *= 10;
	}
	out *= sign;
	return out;
}