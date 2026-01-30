include ../make.config

ifdef TARGET
TARGETPREFIX=$(TARGET)-
else
TARGETPREFIX=
endif
CC=$(TARGETPREFIX)gcc
AR=$(TARGETPREFIX)ar
NASM=nasm
CFLAGS?=-Wall -Wextra -Iinclude -nostdlib -fno-builtin -g
PREFIX?=./sysroot

COBJS=$(LIBC_OBJS)

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

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

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
	rm -f $(OBJS)
	rm -f libc.a
