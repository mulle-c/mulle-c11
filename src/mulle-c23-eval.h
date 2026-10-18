//
//  mulle-c23-eval.h
//  mulle-c11
//
//
//  Copyright (c) 2023 Nat! - Mulle kybernetiK.
//  All rights reserved.
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
#ifndef mulle_c23_eval_h__
#define mulle_c23_eval_h__


//
// Everything in this header needs __VA_OPT__, which is C23.
//
// gcc and clang also accept it before C23 as an extension, so the gate uses the
// capability probe (MULLE_C_HAS_VA_OPT) rather than __STDC_VERSION__: gcc in
// -std=c11 mode answers yes, while `gcc -std=c11 -pedantic-errors` correctly
// rejects it as "not available until C23". TinyCC 0.9.27 has no __VA_OPT__ in
// any mode, so including this header there is an error by design; the mulle-core
// test suite skips these tests when the feature is missing.
//
#include "mulle-c11-eval.h"

#if ! MULLE_C_HAS_VA_OPT
# error "mulle-c23-eval.h requires __VA_OPT__ (C23), which this compiler does not have"
#endif


#define MULLE_C_VA_ARGS_COUNT( ...) \
   MULLE_C_VA_ARGS_15( dummy __VA_OPT__(,) __VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


#define MULLE_C_HAS_ARGS( ...)     MULLE_C_HAS_ARGS_ ## __VA_OPT__(1) ()
#define MULLE_C_HAS_ARGS_()        0
#define MULLE_C_HAS_ARGS_1()       1

#define MULLE_C_IS_EMPTY( ...)  \
        _MULLE_C_IS_ ##  __VA_OPT__( NON_) ## EMPTY
#define _MULLE_C_IS_NON_EMPTY    0
#define _MULLE_C_IS_EMPTY        1

#define MULLE_C_VA_ARGS_WITH_DEFAULT( d, ...)  \
        _MULLE_C_ ##  __VA_OPT__( NON_) ## EMPTY_VA_ARGS_WITH_DEFAULT( d, __VA_ARGS__ )
#define MULLE_C_VA_ARGS_0_WITH_DEFAULT( d, ...)  \
        _MULLE_C_ ##  __VA_OPT__( NON_) ## EMPTY_VA_ARGS_WITH_DEFAULT( d, MULLE_C_VA_ARGS_0( __VA_ARGS__))

#define _MULLE_C_NON_EMPTY_VA_ARGS_WITH_DEFAULT( d, ...)  __VA_ARGS__
#define _MULLE_C_EMPTY_VA_ARGS_WITH_DEFAULT( d, ...)      d



// this is actually original, yay
#define MULLE_C_FOR_EACH_WITH_SEPARATOR( macro, s, sep, first, ...) \
    macro( first, s) __VA_OPT__( sep ) \
    MULLE_C_WHEN( MULLE_C_HAS_ARGS(__VA_ARGS__)) \
    ( \
        MULLE_C_OBSTRUCT( MULLE_C_FOR_EACH_WITH_SEPARATOR_INDIRECT) () \
        ( \
            macro, s ## i, sep, __VA_ARGS__ \
        ) \
    )

#define MULLE_C_FOR_EACH_WITH_SEPARATOR_INDIRECT() \
    MULLE_C_FOR_EACH_WITH_SEPARATOR

#define MULLE_C_FOR_EACH( macro, first, ...) \
    MULLE_C_FOR_EACH_WITH_SEPARATOR( macro, v, , first __VA_OPT__(,) __VA_ARGS__)


//
#define _MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( macro, s, first, ...) \
    macro( first, s) __VA_OPT__( , ) \
    MULLE_C_WHEN( MULLE_C_HAS_ARGS(__VA_ARGS__)) \
    ( \
        MULLE_C_OBSTRUCT( _MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR_INDIRECT) () \
        ( \
            macro, s ## i, __VA_ARGS__ \
        ) \
    )

#define _MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR_INDIRECT()  \
   _MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR

// Emit a comma separated list. Macro should be defined like this:
//
// #define macro( argument, identifier)
//
// Argument will be each vararg in sequence. So with three varargs, the
// macro will be called three times.
// The identifier will be unique within the expansion (but very ugly).
// Call this by wrapping it in MULLE_C_EVAL
// e.g.
// #define field( value, identifier)   identifier = value
// MULLE_C_EVAL( MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( field, 1, 2, 3))
// Expect: v = 1, vi = 2, vii = 3
//

#define MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( macro, first, ...) \
    _MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( macro, v, first __VA_OPT__(,) __VA_ARGS__)


/* Example:
   Create a struct from values and initialize it.
   Step 1. Figure out type of value with MULLE_C_TYPE_OF (mulle-c23-feature.h),
           create a field in the struct for it (STRUCT_FIELD).
   Step 2. Create an initializer with the values (STRUCT_VALUE)
   Step 3. Create the struct (STRUCT_FOR_VALUES)
   Step 4. Execute (MULLE_C_EVAL)

   #define STRUCT_FIELD( expr, s) MULLE_C_TYPE_OF( expr)  s;
   #define STRUCT_VALUE( expr, s) .s = expr

   #define STRUCT_FOR_VALUES( name, ...)                                                 \
      struct                                                                             \
      {                                                                                  \
        MULLE_C_EVAL( MULLE_C_FOR_EACH( STRUCT_FIELD, __VA_ARGS__))                      \
      } name =                                                                           \
      {                                                                                  \
        MULLE_C_EVAL( MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( STRUCT_VALUE, __VA_ARGS__)) \
      }
   MULLE_C_EVAL( STRUCT_FOR_VALUES( my_struct, 1.0f, "VfL Bochum", 1848LL))
*/


#endif
