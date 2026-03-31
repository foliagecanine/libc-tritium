# libc-tritium
TritiumOS C and C++ Libraries

> [!WARNING]  
> These libraries are not standards-compliant, so be sure to familiarize yourself with the library first before assuming functionality.

## Building the C/C++ Compiler
See https://github.com/foliagecanine/tritium-compiler for information on how to build i686-tritium-gcc and i686-tritium-g++.

## Building the libraries
First go into the make.config and change the PREFIX and CCVER.  
Prefix should be the same PREFIX you used to build the C compiler.  
CCVER should be the version of GCC you built.  

You can then run one of the following commands based on what you need:
- `make`: builds libc, the libm stub, and libstdc++
- `make install`: builds libc, the libm stub, and libstdc++, then installs it to the compiler's default libraries directory
- `make libc`: builds only libc
- `make libstdc++`: builds only the libm stub and libstdc++
- `make install-libc`: builds only libc and installs it to the compiler's default libraries directory
- `make install-libstdc++`: builds only the libm stub and libstdc++ and installs it to the compiler's default libraries directory

After installing a library, GCC/G++ will automatically include it: 
```
i686-tritium-gcc main.c -o OUTPUT.PRG
i686-tritium-g++ main.cpp -o OUTPUT.PRG
```