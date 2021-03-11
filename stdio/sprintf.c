#include <stdio.h>

char *out;

bool sprint(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		*(out++) = data[i];
	return true;
}

size_t remain;

bool snprint(const char *data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < (remain-- < length ? remain : length); i++)
		*(out++) = data[i];
	return true;
}

int sprintf(char *s, const char *format, ...) {
	va_list parameters;
	va_start(parameters, format);
	out = s;
	int written = _printf_template(sprint, format, parameters);
	va_end(parameters);
	return written;
}

int vsprintf(char *s, const char *format, va_list arg) {
	out = s;
	int written = _printf_template(sprint, format, arg);
	return written;
}

int snprintf(char *s, size_t n, const char *format, ...) {
	va_list parameters;
	va_start(parameters, format);
	out = s;
	remain = n;
	int written = _printf_template(snprint, format, parameters);
	va_end(parameters);
	return written;
}

int vsnprintf(char *s, size_t n, const char *format, va_list arg) {
	out = s;
	remain = n;
	int written = _printf_template(snprint, format, arg);
	return written;
}

