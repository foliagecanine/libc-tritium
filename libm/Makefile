include ../make.config

ifdef TARGET
TARGETPREFIX=$(TARGET)-
else
TARGETPREFIX=
endif
CC=$(TARGETPREFIX)gcc
AR=$(TARGETPREFIX)ar
NASM=nasm
CFLAGS?=-Iinclude -nostdlib -fno-builtin -g
PREFIX?=./sysroot

COBJS=\
math/math.o \

AOBJS=\

OBJS=\
$(AOBJS) \
$(COBJS)

.PHONY: all clean install
.SUFFIXES: .o .c. .asm

all: libm.a $(AOBJS)

libm.a: $(COBJS)
	$(AR) cr libm.a $(COBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.asm.o:
	$(NASM) -felf32 $< -o $@

install: libm.a $(AOBJS)
	mkdir -p $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/include
	cp libm.a $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/libm.a
	cp include $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER) -r

clean:
	rm -f $(OBJS)
	rm -f libm.a
