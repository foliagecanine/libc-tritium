#include <errno.h>

int errno = 0;

void _set_errno(int e) {
	errno = e;
}

int _errno() {
	return errno;
}

const char *_errno_strings[] = {
	"No error",
	"Operation not permitted",
	"No such file or directory",
	NULL,
	NULL,
	"I/O error", // 5
	NULL,
	NULL,
	NULL,
	"Bad file number",
	NULL, // 10
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 15
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 20
	"Is a directory",
	"Invalid argument",
	NULL,
	"Too many open files",
	NULL, // 25
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 30
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 35
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 40
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 45
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 50
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 55
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 60
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 65
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 70
	NULL,
	NULL,
	NULL,
	NULL,
	"Value too large for defined data type", // 75
};

void perror(const char *s) {
	if (errno > sizeof(_errno_strings)/sizeof(_errno_strings[0]) || _errno_strings[errno] == NULL)
		fprintf(stderr, "%s : Unknown error.", s);
	else
		fprintf(stderr, "%s : %s.", s, _errno_strings[errno]);
}

const char *strerror(int e) {
	if (errno > sizeof(_errno_strings)/sizeof(_errno_strings[0]) || _errno_strings[errno] == NULL)
		return "Unknown error";
	else
		return _errno_strings[e];
}