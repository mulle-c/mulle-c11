# mulle-c11

#### #️⃣ Cross-platform C compiler glue

A C header that enables more feature-rich compilation across various compilers
and platforms.

For example `MULLE_C11_CONSTRUCTOR( f) void  f( void);` will expand differently, depending on the compiler and operating system:

##### clang/gcc

```
__attribute__((constructor)) void  f( void);
``` 

##### MicroSoft Windows

```
static void f(void);
  __declspec(allocate(".CRT$XCU")) void (*f_)(void) = f;
  __pragma(comment(linker,"/include:" p "f_"))
```


Used in various other mulle-projects.


Build Status | Release Version
-------------|-----------------------------------
[![Build Status](https://travis-ci.org/mulle-c/mulle-c11.svg?branch=release)](https://travis-ci.org/mulle-c/mulle-c11) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-c11.svg) [![Build Status](https://travis-ci.org/mulle-c/mulle-c11.svg?branch=release)](https://travis-ci.org/mulle-c/mulle-c11)


## Install

Install the prerequisites first:

| Prerequisites                                 |
|-----------------------------------------------|
| [cmake](cmake.org)                            |


Install into /usr/local:

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
         -DCMAKE_PREFIX_PATH=/usr/local \
         -DCMAKE_BUILD_TYPE=Release .. ;
   make install
)
```


## Author

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)
