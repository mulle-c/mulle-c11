### 4.9.1



feature: add count-leading-zeros and log2 floor helpers

* new ``mulle_c_clz`,` ``mulle_c_clzl`,` and ``mulle_c_clzll`` for counting leading zero bits
* new ``mulle_c_log2_floor`` returning floor(log2(value)) as an unsigned int, defined for 0 as 0
* portable fallbacks used automatically when the compiler lacks the builtins
* ``MULLE_C11_NO_BUILTINS`` forces the portable implementations, also serving as an escape hatch for broken builtins



* remove codeql/semgrep here, defer to mulle-core to run it (saves money)
