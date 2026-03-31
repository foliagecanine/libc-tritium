include make.config

.PHONY: libc libstdc++ all install-libc install-libstdc++ install clean

libc:
	$(MAKE) -C libc

libstdc++:
	$(MAKE) -C libm
	$(MAKE) -C libstdc++

all: libc libstdc++

install-libc:
	$(MAKE) -C libc install

install-libstdc++:
	$(MAKE) -C libstdc++ install

install: install-libc install-libstdc++

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C libstdc++ clean
	$(MAKE) -C libm clean
