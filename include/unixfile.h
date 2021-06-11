#ifndef _UNIXFILE_H
#define _UNIXFILE_H

#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>

#define SEEK_SET 1
#define SEEK_CUR 2
#define SEEK_END 3

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define _IONBF 0
#define _IOLBF 0
#define _IOFBF 0

#define BUFSIZ 0

#define mode_t int
#define off_t long

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int open(const char *path, int flags, ...);
int close(int fd);
int creat(const char *path, mode_t mode);
int read(int fd, void *buf, size_t count);
int write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int remove(const char *filename);

int ferror(FILE *fp);
int feof(FILE *fp);
FILE *fopen(const char *filename, const char *mode);
FILE *freopen(const char *filename, const char *mode, FILE *fp);
int fclose(FILE *fp);
int fflush(FILE *fp);
long int ftell(FILE *fp);
int fseek(FILE *fp, off_t offset, int whence);
void rewind(FILE *fp);
int fputc(int c, FILE *fp);
#define putc(c,fp) fputc(c,fp)
int fputs(const char *s, FILE *fp);
int fgetc(FILE *fp);
char *fgets(char *buf, int n, FILE *fp);
int ungetc(int c, FILE *fp);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);
int vfprintf(FILE *fp, const char *format, va_list parameters);
int fprintf(FILE *fp, const char *format, ...);
int fileno(FILE *fp);

int setvbuf(FILE *fp, char *buf, int mode, size_t size);

FILE *tmpfile(void);

#endif
