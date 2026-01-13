## 4.7.0


* clarified that quickstart creates a complete setup
* added vibecoding setup step to quickstart flow


feat: add C11 alignment header

* new mulle-c11-align.h header with portable alignof/alignas macros
* improved Windows BOOL compatibility requiring early include
* `MULLE_C_WEAK` attribute for weak symbol linking
* `MULLE_C_NO_INSTRUMENT_FUNCTION` attribute for profiling hooks
