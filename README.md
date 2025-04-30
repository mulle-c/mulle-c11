# mulle-c11

#### 🔀 Cross-platform C compiler glue (and some cpp conveniences)

This project provides a C header that enables more feature-rich compilation
across various compilers and platforms. It also contains the basic
documentation for mulle-c development. mulle-c11 is used by all mulle-c or
mulle-objc projects.



| Release Version                                       | Release Notes  | AI Documentation
|-------------------------------------------------------|----------------|---------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-c11.svg) [![Build Status](https://github.com/mulle-c/mulle-c11/workflows/CI/badge.svg)](//github.com/mulle-c/mulle-c11/actions) | [RELEASENOTES](RELEASENOTES.md) | [DeepWiki for mulle-c11](https://deepwiki.com/mulle-c/mulle-c11)


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
* provides support for constructor and destructor functions 
* provides a collection of undocumented, fancy preprocessor evaluation macros in [mulle-c11/mulle-c11-eval.h](src/mulle-c11-eval.h)
* provides `__LITTLE_ENDIAN__` and `__BIG_ENDIAN__` to be queried with `#if` in [mulle-c11/mulle-c11-endian.h](src/mulle-c11-endian.h)


## API

* [SYNTAX.md](dox/SYNTAX.md) explains the naming scheme in data structures used throughout the mulle-c projects




## Preprocessor Conveniences

| mulle-c11                      | Description                                        |
|--------------------------------|----------------------------------------------------|
| `MULLE_C_ASSERT`               | Perform a compile time assertion (must be placed inside a function)
| `MULLE_C_CONCAT`               | Concatenate the two given identifiers
| `MULLE_C_CONSTRUCTOR`          | Constructor function executed on load
| `MULLE_C_GLOBAL`               | Declare a global variable (`extern` on Unix, `declspec...` on Windows)
| `MULLE_C_STRINGIFY`            | Stringify the given identifier
| `__has_attribute( x)`          | If the compiler does not support `__has_attribute` this will always return 0
| `__has_builtin( x)`            | If the compiler does not support `__has_builtin` this will always return 0
| `__has_feature( x)`            | If the compiler does not support `__has_feature` this will always return 0


## Cross platform code generation hints

Some gcc builtins are provided, in case the compiler does not support them.

| mulle-c11                      | Description                                          |
|--------------------------------|------------------------------------------------------|
| `MULLE_C_LIKELY( expr)`        | Predict branch to be taken
| `MULLE_C_UNLIKELY( expr)`      | Predict branch not to be taken
| `MULLE_C_EXPECT( expr,value)`  | Special case when expression does not return 0 / 1 (or for style)| `mulle_c_popcount`   | Count the number of set bits in `unsigned int`                |
| `mulle_c_popcountl`            | Count the number of set bits in `unsigned long`      |
| `mulle_c_popcountll`           | Count the number of set bits in `unsigned long long` |


## Cross platform attributes

Compilation hints like  `__attribute__(( <name>))` are usually only available
for gcc and clang. These mulle-c11 macros allow compilation with other
compilers.

| Attribute         | mulle-c11                | Description                                        |
|-------------------|--------------------------|----------------------------------------------------|
| `always_inline`   | `MULLE_C_ALWAYS_INLINE`  | Force inlining of the annotated function
| `const`           | `MULLE_C_CONST`          | Mark the function return value as constant for same input
| `deprecated`      | `MULLE_C_DEPRECATED`     | Mark the function as deprecated
| `never_inline`    | `MULLE_C_NEVER_INLINE`   | Prevent inlining of the annotated function
| `nonnull`         | `MULLE_C_NONNULL_FIRST`  | Mark the first function parameter as not accepting NULL. There is also `MULLE_C_NONNULL_SECOND` and combinations like `MULLE_C_NONNULL_FIRST_FOURTH` up to five parameters
| `returns_nonnull` | `MULLE_C_NONNULL_RETURN` | Mark the function as never returning NULL
| `noreturn`        | `MULLE_C_NO_RETURN`      | Mark the function as not returning (e.g. abort)
| `pure`            | `MULLE_C_PURE`           | Mark the function as having no side effects
| `unused`          | `MULLE_C_UNUSED`         | Mark the parameter as unused

use `MULLE_C_ALWAYS_STATIC_INLINE` in your function definitions though, if
you want to keep windows happier:

``` c
MULLE_C_ALWAYS_STATIC_INLINE void  foo( void)
{
}
```


### Constructor / destructor functions

| mulle-c11                | Description                                        |
|--------------------------|----------------------------------------------------|
| `MULLE_C_CONSTRUCTOR`    | Constructor function executed on unload
| `MULLE_C_DESTRUCTOR`     | Destructor function executed on unload

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

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-c11:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-c/mulle-c11/archive/latest.tar.gz
```

### Legacy Installation


Download the latest [tar](https://github.com/mulle-c/mulle-c11/archive/refs/tags/latest.tar.gz) or [zip](https://github.com/mulle-c/mulle-c11/archive/refs/tags/latest.zip) archive and unpack it.

Install **mulle-c11** into `/usr/local` with [cmake](https://cmake.org):

``` sh
PREFIX_DIR="/usr/local"
cmake -B build                               \
      -DMULLE_SDK_PATH="${PREFIX_DIR}"       \
      -DCMAKE_INSTALL_PREFIX="${PREFIX_DIR}" \
      -DCMAKE_PREFIX_PATH="${PREFIX_DIR}"    \
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



