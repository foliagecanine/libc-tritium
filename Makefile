include make.config

.PHONY: all install clean

all:
	$(MAKE) -C libc
	$(MAKE) -C libstdc++
	$(MAKE) -C libm

install:
	$(MAKE) -C libc install
	$(MAKE) -C libstdc++ install
	$(MAKE) -C libm install

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C libstdc++ clean
	$(MAKE) -C libm clean