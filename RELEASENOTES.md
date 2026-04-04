## 4.8.0





feature: add portable `mulle_c_memcpy` wrapper

* new static inline `mulle_c_memcpy(dst,` src, n) that uses `__builtin_memcpy` when available
* falls back to calling libc memcpy when the builtin is not present



feature: reorganize headers for windows

* since windows code needs to have the proper BOOL (ours) eventually mulle-c11.h now includes book and integer and endian by default
* new byte-swap API for integers and floating-point values, including host↔big/little conversions
* **BREAKING**: remove NSSwap*/MulleObjCSwap* inline helpers from mulle-c11-endian.h; migrate to `mulle_swap_*`  helpers, move NS code back to MUlleObjC



feature: expand portable attribute and export macros

* add `MULLE_C_WEAK,` `MULLE_C_TYPE_OF,` and mulle-objc confined-loop/return annotations for cross-compiler builds
* add `MULLE_C_GLOBAL_VAR` to make Windows DLL export of global variables explicit and consistent
* **BREAKING** remove `MULLE_C_RENDEZVOUS_SYMBOL` and `MULLE_C_EXTERN_RENDEZVOUS_SYMBOL` from the public header
* add `MULLE_C_HAS_VA_OPT` detection helper for advanced preprocessor metaprogramming
