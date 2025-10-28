#ifndef _ERRNO_H
#define _ERRNO_H

#include <stdio.h>
#include <unixfile.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

extern int errno;

void _set_errno(int e);
void perror(const char *s);
const char *strerror(int e);

#define EPERM 		1
#define ENOENT 		2
#define EIO			5
#define EBADF 		9
#define EISDIR 		21
#define EINVAL 		22
#define EMFILE 		24
#define EOVERFLOW	75

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif

#endif
