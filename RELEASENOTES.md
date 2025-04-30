### 4.6.1

* added MULLE_C_STATIC_ALWAYS_INLINE
* introduced MULLE_C_FALLTHROUGH

## 4.6.0

* added `MULLE_C_STRINGIFY_MACRO`


## 4.5.0



* NSInteger update with NSIntegerMaximum and NSIntegerMinimum
* Moved endian swap code from MulleObjC to mulle-c11 for better code organization
  * Preserved Darwin naming conventions for better self-documentation
  * Added functions like NSSwapShort, NSSwapInt, NSSwapLongLong etc.
* Added mulle-c11-endian.h providing cross-platform endianness checks
* Added mulle-c11-bool.h with BOOL type support
* Added mulle-c11-integer.h with NSInteger and NSUInteger types
* Added popcount functionality:
  * `mulle_c_popcount` for unsigned int
  * `mulle_c_popcountl` for unsigned long
  * `mulle_c_popcountll` for unsigned long long
* Enhanced compiler directives:
  * Reworked `MULLE_C_NONNULL_...` macros
  * Added `MULLE_C_LIKELY,` `MULLE_C_EXPECT,` `MULLE_C_UNLIKELY`
  * Fixed `MULLE_C_ALWAYS_INLINE` for Windows
* Simplified `__has_builtin` checks with custom implementation for non-supporting compilers
* Updated CMake build system for better cross-platform support
* Removed STEAL.md as it's now obsolete due to clib integration
* Bumped version to 4.5.0

* mulle-c11-endian.h (optional include) provides endianness checks across compilers/platforms

* simplify some `has_builtin` checks, with a custom `has_builtin` if the compilerdoesn't provide it


## 4.4.0

* added mulle-c11-bool.h for BOOL
* added mulle-c11-integer for NSInteger and NSUInteger
* added `mulle_c_popcount` and relatives
* rework `MULLE_C_NONNULL_...`
* add `MULLE_C_LIKELY,` `MULLE_C_EXPECT,` `MULLE_C_UNLIKELY`


## 4.3.0

* remove package.json as it conflicts with clib.json
* mulle-c11-eval.h is a new header
* add ``MULLE_C_UNUSED``


### 4.2.1

* Various small improvements

## 4.2.0

* improved GLOBAL attributes for Windows
* change GLOBAL definition for Windows


### 4.1.2

* Various small improvements

### 4.1.1

* -Wobjc-protocol-method-implementation no longer disabled

## 4.1.0

* added STEAL.md dox
* moved syntax dox from mulle-container here
* improved stdalign detection


# 4.0.0

* added NONNULL parameter checks (from mulle-container) and renamed existing `NON_NULL` defines to NONNULL
* add `MULLE_C_DESTRUCTOR` and some tests


### 3.1.4

* Various small improvements

### 3.1.3

* modernized to mulle-sde with .mulle folder

### 3.1.2

* improve README

### 3.1.1

* simplified CMakeLists.txt

## 3.1.0

* add `__has_feature` and `__has_attribute` capability (somewhat experimentally)


### 3.0.2

* fix again, what had been fixed already :(

### 3.0.1

* fix what had been fixed already :(

# 3.0.0

* MULLE_C_CONSTRUCTOR gains a parameter for WINDOWS

### 2.0.2

* use old .travis.yml file

### 2.0.1

* fix travis.yml

# 2.0.0

* migrated to mulle-sde
* renamed header to mulle-c11.h with a hyphen

### 1.3.5

* fixed scion wrapper command

### 1.3.3

* refinements for mulle-configuration 3.1

### 1.3.1

* MULLE_C11_NO_NOOB_WARNINGS diagnostic switch added
* improve life for cl.exe, by making it worse for clang and gcc (_MULLE_C_...)

### 1.2.5

** modernize project

### 1.2.3

* make project "C" for cmake

### 1.2.1

* be smarter about gcc 4.8 not allowing non_null returns...


### 1.1.3

* modernize project

1.1.2
===

* community release

### 1.0.5

1.0.6
===
* improved README


1.0.5
===
* merged in community release

1.0.4
====

* community release

1.0.2-1.0.3
=====

* remove obsolte install.sh file
* improve release process
