#include <stdlib.h>

static int _chartoval(char c) {
    if (isdigit(c))
        return c-'0';
    if (isxdigit(c)) {
        return (toupper(c)-'A')+10;
    }
    return -1;
}

unsigned long int strtoul (const char *str, char **endptr, int base) {
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
	while (_chartoval(*cstr)!=-1 && _chartoval(*cstr) < base)
	    cstr++;
	if (endptr != NULL)
		*endptr = (char *)cstr;
	unsigned long int multiplier = 1;
	unsigned long int out = 0;
	while (cstr-- != strbegin) {
		if (out + (_chartoval(*cstr) * multiplier) < out)
			return ULONG_MAX;
		out += _chartoval(*cstr) * multiplier;
		multiplier *= base;
	}
	out *= sign;
	return out;
}

long int strtol (const char *str, char **endptr, int base) {
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
	while (_chartoval(*cstr)!=-1 && _chartoval(*cstr) < base)
	    cstr++;
	if (endptr != NULL)
		*endptr = (char *)cstr;
	long int multiplier = 1;
	long int out = 0;
	while (cstr-- != strbegin) {
		if (out + (_chartoval(*cstr) * multiplier) < out)
			return LONG_MAX;
		out += _chartoval(*cstr) * multiplier;
		multiplier *= base;
	}
	out *= sign;
	return out;
}

unsigned long long int strtoull (const char *str, char **endptr, int base) {
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
	while (_chartoval(*cstr)!=-1 && _chartoval(*cstr) < base)
	    cstr++;
	if (endptr != NULL)
		*endptr = (char *)cstr;
	unsigned long long int multiplier = 1;
	unsigned long long int out = 0;
	while (cstr-- != strbegin) {
		if (out + (_chartoval(*cstr) * multiplier) < out)
			return ULLONG_MAX;
		out += _chartoval(*cstr) * multiplier;
		multiplier *= base;
	}
	out *= sign;
	return out;
}

long long int strtoll (const char *str, char **endptr, int base) {
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
	while (_chartoval(*cstr)!=-1 && _chartoval(*cstr) < base)
	    cstr++;
	if (endptr != NULL)
		*endptr = (char *)cstr;
	long long int multiplier = 1;
	long long int out = 0;
	while (cstr-- != strbegin) {
		if (out + (_chartoval(*cstr) * multiplier) < out)
			return LLONG_MAX;
		out += _chartoval(*cstr) * multiplier;
		multiplier *= base;
	}
	out *= sign;
	return out;
}
