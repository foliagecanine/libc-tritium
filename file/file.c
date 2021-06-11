#include <stdio.h>

static char *expand_fname(const char *filename) {
	char *retval;
	if (filename[1]!=':') {
		char *cd = getenv("CD");
		if (!cd) {
			if (!retval)
				return NULL;
		}
		retval = malloc(strlen(filename)+strlen(cd)+1);
		if (!retval)
			return NULL;
		strcpy(retval,cd);
		strcpy(retval+strlen(cd),filename);
		retval[strlen(cd)+strlen(filename)] = 0;
		return retval;
	}
	retval = malloc(strlen(filename)+1);
	if (!retval)
		return NULL;
	strcpy(retval,filename);
	retval[strlen(filename)] = 0;
	return retval;
}

FILE null_file = {0};

FILE *openfile (const char* filename, const char* mode) {
	FILE *fp;
	if (mode[0]=='w') {
		deletefile(filename);
		fp = createfile(filename);
	} else {
		fp = calloc(1,sizeof(FILE));
	}
	if (!fp)
		return &null_file;
	char *full_filename = expand_fname(filename);
	if (!full_filename)
		return fp;
	_syscall3(12,(uintptr_t)fp,(uintptr_t)full_filename,(uintptr_t)mode);
	free(full_filename);
	return fp;
}

uint8_t readfile (FILE *t, char *buf, uint64_t start, uint32_t len) {
	uint8_t retval;
	uint32_t starth = start>>32;
	uint32_t startl = start&0xFFFFFFFF;
	retval = (uint8_t)_syscall5(13,(uintptr_t)t,(uintptr_t)buf,starth,startl,len);
	return retval;
}

uint8_t writefile (FILE *t, char *buf, uint64_t start, uint32_t len) {
	uint8_t retval;
	uint32_t starth = start>>32;
	uint32_t startl = start&0xFFFFFFFF;
	retval = (uint8_t)_syscall5(14,(uintptr_t)t,(uintptr_t)buf,starth,startl,len);
	return retval;
}

FILE *createfile(const char *filename) {
	FILE *fp = calloc(1,sizeof(FILE));
	if (!fp)
		return &null_file;
	char *full_filename = expand_fname(filename);
	if (!full_filename)
		return fp;
	_syscall2(15,(uintptr_t)full_filename,(uintptr_t)fp);
	free(full_filename);
	return fp;
}

uint8_t deletefile(const char *filename) {
	char *full_filename = expand_fname(filename);
	if (!full_filename)
		return 1;
	uint8_t retval = _syscall1(16,(uintptr_t)full_filename);
	free(full_filename);
	return retval;
}

bool existfile(const char *filename) {
	FILE f;
	if (!filename)
		return false;
	char *full_filename = expand_fname(filename);
	if (!full_filename)
		return false;
	_syscall3(12,(uintptr_t)&f,(uintptr_t)full_filename,(uintptr_t)"r");
	free(full_filename);
}

FILE *finddir(FILE *d, char* buf, uint32_t n) {
	FILE *fp = calloc(1,sizeof(FILE));
	if (!fp)
		return &null_file;
	_syscall4(18,(uintptr_t)d,(uintptr_t)fp,(uintptr_t)buf,n);
	return fp;
}

int closefile(FILE *fp) {
	if (!fp)
		return 1;
	free(fp);
	return 0;
}