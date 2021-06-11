include make.config

ifdef TARGET
TARGETPREFIX=$(TARGET)-
else
TARGETPREFIX=
endif
CC=$(TARGETPREFIX)gcc
AR=$(TARGETPREFIX)ar
NASM=nasm
CLFAGS?=-Iinclude -nostdlib -fno-builtin -g
PREFIX?=./sysroot

COBJS=\
file/file.o \
file/unixfile.o \
gui/drawrect.o \
gui/fileselector.o \
io/getchar.o \
io/tty.o \
io/errno.o \
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
stdio/sprintf.o \
string/memcmp.o \
string/memset.o \
string/memcpy.o \
string/memmove.o \
string/memchr.o \
string/strchr.o \
string/strcmp.o \
string/strncmp.o \
string/strcpy.o \
string/strncpy.o \
string/strcut.o \
string/strlen.o \
string/strrchr.o \
string/strcspn.o \
string/strspn.o \
string/strpbrk.o \
string/strstr.o \
string/strcat.o \
sys/sys.o \
stdlib/malloc.o \
stdlib/strto.o \
stdlib/atoi.o \
stdlib/math.o \
stdlib/qsort.o \
stdlib/abort.o \
ctype/isdigit.o \
ctype/ispunct.o \
ctype/islower.o \
ctype/isspace.o \
ctype/isupper.o \
ctype/isalpha.o \
ctype/tolower.o \
ctype/toupper.o \
ctype/isxdigit.o \
ctype/isalnum.o \

AOBJS=\
crt0.o \
crti.o \
crtn.o \

OBJS=\
$(AOBJS) \
$(COBJS)

.PHONY: all clean install
.SUFFIXES: .o .c. .asm

all: libc.a $(AOBJS)

libc.a: $(COBJS)
	$(AR) cr libc.a $(COBJS)

.c.o: %.c
	$(CC) $(CLFAGS) -c $< -o $@

.asm.o:
	$(NASM) -felf32 $< -o $@

install: libc.a $(AOBJS)
	mkdir -p $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/include
	cp crt0.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp crtn.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp crti.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp libc.a $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/libc.a
	cp include $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER) -r

clean:
	rm $(OBJS)
	rm libc.a
