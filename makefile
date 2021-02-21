include make.config

ifdef TARGET
TARGETPREFIX=$(TARGET)-
else
TARGETPREFIX=
endif
CC=$(TARGETPREFIX)gcc
AR=$(TARGETPREFIX)ar
NASM=nasm
CLFAGS?=
PREFIX?=./sysroot

COBJS=\
file/file.o \
gui/drawrect.o \
gui/fileselector.o \
io/getchar.o \
io/tty.o \
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
string/memcmp.o \
string/memset.o \
string/memcpy.o \
string/memmove.o \
string/strchr.o \
string/strcmp.o \
string/strcpy.o \
string/strcut.o \
string/strlen.o \
string/strrchr.o \
string/tolower.o \
string/toupper.o \
sys/sys.o \

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
	$(CC) -c $< -o $@ $(CFLAGS)

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
