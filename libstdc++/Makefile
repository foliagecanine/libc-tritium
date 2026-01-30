include ../make.config

ifdef TARGET
TARGETPREFIX=$(TARGET)-
else
TARGETPREFIX=
endif
CXX=$(TARGETPREFIX)g++
AR=$(TARGETPREFIX)ar
NASM=nasm
CXXFLAGS?=-Wall -Wextra -Iinclude -I../libc/include -nostdlib -fno-builtin -fno-exceptions -g -std=c++11 
PREFIX?=./sysroot

CPP_OBJS=$(LIBSTDCXX_OBJS)

LIBC_PATH=../libc/

CPP_LIBC_OBJS=$(LIBC_OBJS)
CPP_LIBC_OBJS := $(addprefix  $(LIBC_PATH), $(CPP_LIBC_OBJS))

CPP_OBJS += $(CPP_LIBC_OBJS)

A_OBJS=\
crt0.o \
crti.o \
crtn.o \

OBJS=\
$(AOBJS) \
$(COBJS)

.PHONY: all clean install
.SUFFIXES: .o .cpp .c .asm

all: libstdc++.a $(A_OBJS) $(CPP_OBJS)

libstdc++.a: $(CPP_OBJS)
	$(AR) cr libstdc++.a $(CPP_OBJS)

.c.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.asm.o:
	$(NASM) -felf32 $< -o $@

install: libstdc++.a $(A_OBJS)
	mkdir -p $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/include
	cp crt0.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp crtn.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp crti.o $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)
	cp libstdc++.a $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER)/libstdc++.a
	cp include $(PREFIX)/lib/gcc/$(TARGET)/$(CCVER) -r

clean:
	rm -f $(OBJS)
	rm -f libstdc++.a
