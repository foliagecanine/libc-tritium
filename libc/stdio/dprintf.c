#include <stdio.h>

static int dprint(const char *data, size_t length)
{
    for (size_t i = 0; i < length; i++)
        serial_putchar(data[i]);
    return length;
}

static size_t remain;

static int dnprint(const char *data, size_t length)
{
    for (size_t i = 0; i < length && i < remain--; i++)
        serial_putchar(data[i]);
    return length;
}

int dprintf(const char *format, ...)
{
    va_list parameters;
    va_start(parameters, format);
    int written = __print_formatted(dprint, format, parameters);
    va_end(parameters);
    return written;
}

int vdprintf(const char *format, va_list arg)
{
    int written = __print_formatted(dprint, format, arg);
    return written;
}
