# libc-tritium
TritiumOS C Library

## Building the C Compiler
See https://github.com/foliagecanine/tritium-compiler for information on how to build i686-tritium-gcc.

## Building the C Library
First go into the make.config and change the PREFIX and CCVER.  
Prefix should be the same PREFIX you used to build the C compiler.  
CCVER should be the version of GCC you built.  
  
Run ```make``` to make libc.a as well as crt0.o, crtn.o, and crti.o  
Run ```make install``` to install the library (running make install will automatically run "make").  
  
Now GCC will automatically include the C library when using it:  
```i686-tritium-gcc main.c -o output-program```
