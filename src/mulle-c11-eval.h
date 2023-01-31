//
//  mulle_c11_eval.h
//
//  Copyright © 2022 Mulle kybernetiK. All rights reserved.
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
#ifndef mulle_c11_eval_h__
#define mulle_c11_eval_h__

// MEMO: currently not exposed in mulle-c11.h, because it's fairly obscure
//       and rarely needed

/*
 * EVALUATION FUNCTIONS FOR PREPROCESSOR VARARGS
 */
//
// https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/__VA_ARGS__/count-arguments
//

// treat __VA_ARGS__ like a C array, index starts at 0

// MULLE_C_VA_ARGS_0 can be called MULLE_C_VA_ARGS_0() as a0 will be nothing
#define MULLE_C_VA_ARGS_0(  a0, ...) a0
#define MULLE_C_VA_ARGS_1(  a0, a1, ...) a1
#define MULLE_C_VA_ARGS_2(  a0, a1, a2, ...) a2
#define MULLE_C_VA_ARGS_3(  a0, a1, a2, a3, ...) a3
#define MULLE_C_VA_ARGS_4(  a0, a1, a2, a3, a4, ...) a4
#define MULLE_C_VA_ARGS_5(  a0, a1, a2, a3, a4, a5, ...) a5
#define MULLE_C_VA_ARGS_6(  a0, a1, a2, a3, a4, a5, a6, ...) a6
#define MULLE_C_VA_ARGS_7(  a0, a1, a2, a3, a4, a5, a6, a7, ...) a7
#define MULLE_C_VA_ARGS_8(  a0, a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define MULLE_C_VA_ARGS_9(  a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a9
#define MULLE_C_VA_ARGS_10( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10
#define MULLE_C_VA_ARGS_11( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define MULLE_C_VA_ARGS_12( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) a12
#define MULLE_C_VA_ARGS_13( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) a13
#define MULLE_C_VA_ARGS_14( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) a14
#define MULLE_C_VA_ARGS_15( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) a15

#define MULLE_C_VA_ARGS_COUNT( ...) \
   MULLE_C_VA_ARGS_15( dummy __VA_OPT__(,) __VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

//
// https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
//
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


#define MULLE_C_CAT( a, ...)             MULLE_C_PRIMITIVE_CAT( a, __VA_ARGS__)
#define MULLE_C_PRIMITIVE_CAT( a, ...)   a ## __VA_ARGS__

#define MULLE_C_IIF( c)          MULLE_C_PRIMITIVE_CAT( MULLE_C_IIF_, c)
#define MULLE_C_IIF_0( t, ...)   __VA_ARGS__
#define MULLE_C_IIF_1( t, ...)   t

#define MULLE_C_EAT(...)
#define MULLE_C_EXPAND(...)      __VA_ARGS__
#define MULLE_C_WHEN( c)         MULLE_C_IIF(c)( MULLE_C_EXPAND, MULLE_C_EAT)

#define MULLE_C_EMPTY()
#define MULLE_C_DEFER( id)       id MULLE_C_EMPTY()
#define MULLE_C_OBSTRUCT(...)    __VA_ARGS__ MULLE_C_DEFER( MULLE_C_EMPTY)()

//
// The "eval" trick can be done up to a loop depth of 256. If you need more,
// define more. The default is 64. The higher you go the more the compiler
// slows down though.
//
#define MULLE_C_EVAL256(...)   MULLE_C_EVAL128( MULLE_C_EVAL127( __VA_ARGS__))
#define MULLE_C_EVAL255(...)   MULLE_C_EVAL127( MULLE_C_EVAL127( __VA_ARGS__))
#define MULLE_C_EVAL128(...)   MULLE_C_EVAL64( MULLE_C_EVAL63( __VA_ARGS__))
#define MULLE_C_EVAL127(...)   MULLE_C_EVAL63( MULLE_C_EVAL63( __VA_ARGS__))
#define MULLE_C_EVAL64(...)    MULLE_C_EVAL32( MULLE_C_EVAL31( __VA_ARGS__))
#define MULLE_C_EVAL63(...)    MULLE_C_EVAL31( MULLE_C_EVAL31( __VA_ARGS__))
#define MULLE_C_EVAL32(...)    MULLE_C_EVAL16( MULLE_C_EVAL15( __VA_ARGS__))
#define MULLE_C_EVAL31(...)    MULLE_C_EVAL15( MULLE_C_EVAL15( __VA_ARGS__))
#define MULLE_C_EVAL16(...)    MULLE_C_EVAL8( MULLE_C_EVAL7( __VA_ARGS__))
#define MULLE_C_EVAL15(...)    MULLE_C_EVAL7( MULLE_C_EVAL7( __VA_ARGS__))
#define MULLE_C_EVAL8(...)     MULLE_C_EVAL4( MULLE_C_EVAL3( __VA_ARGS__))
#define MULLE_C_EVAL7(...)     MULLE_C_EVAL3( MULLE_C_EVAL3( __VA_ARGS__))
#define MULLE_C_EVAL4(...)     MULLE_C_EVAL2( MULLE_C_EVAL1( __VA_ARGS__))
#define MULLE_C_EVAL3(...)     MULLE_C_EVAL1( MULLE_C_EVAL1( __VA_ARGS__))
#define MULLE_C_EVAL2(...)     MULLE_C_EVAL1( __VA_ARGS__)
#define MULLE_C_EVAL1(...)     __VA_ARGS__

#define MULLE_C_EVAL(...)      MULLE_C_EVAL64( __VA_ARGS__)

#define MULLE_C_HAS_ARGS( ...)     MULLE_C_HAS_ARGS_ ## __VA_OPT__(1) ()
#define MULLE_C_HAS_ARGS_()        0
#define MULLE_C_HAS_ARGS_1()       1

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


// Example:
// Create a struct from values and initialize it.
// Step 1. Figure out type of value with __typeof__, create a field in the
//         struct for it (STRUCT_FIELD).
// Step 2. Create an initializer with the values (STRUCT_VALUE)
// Step 3. Create the struct (STRUCT_FOR_VALUES)
// Step 4. Execute (MULLE_C_EVAL)
//
// #define STRUCT_FIELD( expr, s) __typeof__( expr)  s;
// #define STRUCT_VALUE( expr, s) .s = expr
//
// #define STRUCT_FOR_VALUES( name, ...)                                                 \
//    struct                                                                             \
//    {                                                                                  \
//      MULLE_C_EVAL( MULLE_C_FOR_EACH( STRUCT_FIELD, __VA_ARGS__))                      \
//    } name =                                                                           \
//    {                                                                                  \
//      MULLE_C_EVAL( MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( STRUCT_VALUE, __VA_ARGS__)) \
//    }
// MULLE_C_EVAL( STRUCT_FOR_VALUES( my_struct, 1.0f, "VfL Bochum", 1848LL))

#endif
