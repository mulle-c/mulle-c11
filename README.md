# mulle-c11

#### 🔀 Cross-platform C compiler glue (and some cpp conveniences)

This project provides a C header that enables more feature-rich compilation
across various compilers and platforms. It also contains the basic
documentation for mulle-c development. mulle-c11 is used by all mulle-c or
mulle-objc projects.


| Release Version                                       | Release Notes
|-------------------------------------------------------|--------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-c11.svg?branch=release) [![Build Status](https://github.com/mulle-c/mulle-c11/workflows/CI/badge.svg?branch=release)](//github.com/mulle-c/mulle-c11/actions)| [RELEASENOTES](RELEASENOTES.md) |


## Features

* includes `<stdalign.h>`, if detected as available, or provides replacement code. This enables `alignof` and ` alignas`.
* provides `__builtin_expect`, if not available.
* provides dummy implementations for `__has_feature` and
`__has_attribute`, which always return 0 (NO).
* provides the `MULLE_C_STRINGIFY` macro, which creates a
string from the given identifier (`MULLE_C_STRINGIFY( a)` creates `"a"`).
* provides the `MULLE_C_CONCAT` macro to concatenate two
identifiers (`MULLE_C_CONCAT( a, b)` creates `ab`).
* provides `MULLE_C_ASSERT` for compile time assertions, e.g. `MULLE_C_ASSERT( sizeof( foo) <= sizeof( void *)`
* provides support for constructor and destructor functions see below
* provides a collection of undocumented, fancy preprocessor evaluation macros in [mulle-c11/mulle-c11-eval.h](src/mulle-c11-eval.h)


## API

* [SYNTAX.md](dox/SYNTAX.md) explains the naming scheme in data structures used throughout the mulle-c projects




## Cross platform attributes

Compilation hints like  `__attribute__(( <name>))` are usually only available
for gcc and clang. These mulle-c11 macros allow compilation with other
compilers.

| Attribute         | mulle-c11                | Description                                        |
|-------------------|--------------------------|----------------------------------------------------|
| `always_inline`   | `MULLE_C_ALWAYS_INLINE`  | Force inlining of function                         |
| `const`           | `MULLE_C_CONST`          | Mark function return value as constant given same input parameters  |
| `deprecated`      | `MULLE_C_DEPRECATED`     | Mark function as deprecated                        |
| `never_inline`    | `MULLE_C_NEVER_INLINE`   | Prevent inlining of function                       |
| `nonnull`         | `MULLE_C_NONNULL_FIRST`  | Marks first function parameter as not accepting NULL. There is also `MULLE_C_NONNULL_SECOND` and combinations like `MULLE_C_NONNULL_FIRST_FOURTH` up to five parameters  |
| `noreturn`        | `MULLE_C_NO_RETURN`      | Mark function as not returning (e.g. `abort`)      |
| `returns_nonnull` | `MULLE_C_NONNULL_RETURN` | Mark function as never returning zero (NULL)       |

### Constructor/destructor example

Constructor functions are executed when the containing object
file is loaded. In a static executable, this is guaranteed before `main`.
In shared library environments, it depends on when the shared library is
loaded. Destructor functions are called before the unloading of the shared
library or before the exit of the executable.

``` c
MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   printf( "load\n");
}
MULLE_C_DESTRUCTOR( unload)
static void   unload( void)
{
   printf( "unload\n");
}
```

`MULLE_C11_CONSTRUCTOR( f) void  f( void);` will expand differently, depending
on the compiler and operating system:

#### clang/gcc

``` c
__attribute__((constructor)) void  f( void);
```

#### MicroSoft Windows

``` c
static void f(void);
  __declspec(allocate(".CRT$XCU")) void (*f_)(void) = f;
  __pragma(comment(linker,"/include:" p "f_"))
```

### You are here

![Overview](overview.dot.svg)





## Add

**This project is a component of the [mulle-core](//github.com/mulle-core/mulle-core) library. As such you usually will *not* add or install it
individually, unless you specifically do not want to link against
`mulle-core`.**


### Add as an individual component

Use [mulle-sde](//github.com/mulle-sde) to add mulle-c11 to your project:

``` sh
mulle-sde add github:mulle-c/mulle-c11
```

To only add the sources of mulle-c11 with dependency
sources use [clib](https://github.com/clibs/clib):


``` sh
clib install --out src/mulle-c mulle-c/mulle-c11
```

Add `-isystem src/mulle-c` to your `CFLAGS` and compile all the sources that were downloaded with your project.


## Install

### Install with mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-c11:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-c/mulle-c11/archive/latest.tar.gz
```

### Manual Installation


Install **mulle-c11** into `/usr/local` with [cmake](https://cmake.org):

``` sh
cmake -B build \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_PREFIX_PATH=/usr/local \
      -DCMAKE_BUILD_TYPE=Release &&
cmake --build build --config Release &&
cmake --install build --config Release
```

## Acknowledgments

The Preprocessor evaluation feature is indebted mostly to
[C Preprocessor tricks, tips, and idioms](https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms) and
[Preprocessor: `__VA_ARGS__` : count arguments](https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/__VA_ARGS__/count-arguments)

## Author

[Nat!](https://mulle-kybernetik.com/weblog) for Mulle kybernetiK



