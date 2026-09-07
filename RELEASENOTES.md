## 4.9.0





feature: add portable rotate-left/right helpers for 32- and 64-bit integers

* new mulle-c11-rotate.h header with ``mulle_rotate_left_uint32`,` ``mulle_rotate_right_uint32`,` ``mulle_rotate_left_uint64`,` and ``mulle_rotate_right_uint64`` inline functions
* functions compile to a single `ror`/`rol` instruction on GCC and Clang at -O2
* guards against undefined behavior when the shift count is zero or equal to the type width
* rotate helpers are included from the umbrella `mulle-c11.h` header



* new Documentation & Guides section in README with API Summary link


### 4.8.1

Various small improvements
