### 4.9.1




feature: add C23 eval and feature headers with capability probes

* new `mulle-c23-eval.h` for ``__VA_OPT__`` based macros `(`MULLE_C_FOR_EACH`,` ``MULLE_C_VA_ARGS_COUNT`,` ``MULLE_C_HAS_ARGS`,` ``MULLE_C_IS_EMPTY`,` ``MULLE_C_VA_ARGS_WITH_DEFAULT`)`
* new `mulle-c23-feature.h` providing ``MULLE_C_TYPE_OF`` `(`__typeof__`)`
* new overridable probes ``MULLE_C_HAS_VA_OPT`` and ``MULLE_C_HAS_TYPEOF`` so consumers can detect/force the C11-only path
* `mulle-c11.h` now pulls the C23 headers in automatically when the features are available
* **BREAKING** ``MULLE_C_TYPE_OF`` and the ``__VA_OPT__`` macros moved out of `mulle-c11-feature.h` / `mulle-c11-eval.h`; include `mulle-c23-feature.h` / `mulle-c23-eval.h` instead









feature: add count-leading-zeros and log2 floor helpers

* new ``mulle_c_clz`,` ``mulle_c_clzl`,` and ``mulle_c_clzll`` for counting leading zero bits
* new ``mulle_c_log2_floor`` returning floor(log2(value)) as an unsigned int, defined for 0 as 0
* portable fallbacks used automatically when the compiler lacks the builtins
* ``MULLE_C11_NO_BUILTINS`` forces the portable implementations, also serving as an escape hatch for broken builtins



* remove codeql/semgrep here, defer to mulle-core to run it (saves money)

## 4.9.0





feature: add portable rotate-left/right helpers for 32- and 64-bit integers

* new mulle-c11-rotate.h header with ``mulle_rotate_left_uint32`,` ``mulle_rotate_right_uint32`,` ``mulle_rotate_left_uint64`,` and ``mulle_rotate_right_uint64`` inline functions
* functions compile to a single `ror`/`rol` instruction on GCC and Clang at -O2
* guards against undefined behavior when the shift count is zero or equal to the type width
* rotate helpers are included from the umbrella `mulle-c11.h` header



* new Documentation & Guides section in README with API Summary link


### 4.8.1

Various small improvements
