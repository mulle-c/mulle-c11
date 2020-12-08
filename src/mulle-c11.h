//
//  mulle_c11.h
//
//  Copyright © 2016 Mulle kybernetiK. All rights reserved.
//  Copyright © 2016 Codeon GmbH. All rights reserved.
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

#ifndef mulle_c11_h__
#define mulle_c11_h__

#ifdef __cplusplus
# error "C++ ? You're doing it wrong."
#endif


#ifndef __has_feature          // Optional.
# define __has_feature( x) 0   // Compatibility with non-clang compilers.
#endif

#ifndef __has_attribute
# define __has_attribute( x) 0
#endif


#define MULLE_C11_VERSION  ((4 << 20) | (1 << 8) | 0)


//
// basic C11 stuff, that's missing on "some" platforms
// https://gcc.gnu.org/wiki/C11Status
//
#ifndef MULLE_C11_NO_STDALIGN
# ifdef _WIN32
#  define MULLE_C11_NO_STDALIGN
# endif

# ifndef __clang__
#  ifdef __GNUC__
#   if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)
#    define MULLE_C11_NO_STDALIGN
#   endif
#  endif
# endif
#endif


#ifdef MULLE_C11_NO_STDALIGN
# define alignof( x)    __alignof( x)
#else
# include <stdalign.h>
#endif


#ifdef _WIN32
# define __builtin_expect( x, y) x
#endif

// The following definitions are for the "outside looking in" not
// for compiling the (shared) library itself.
//
// https://msdn.microsoft.com/en-us/library/aa271769(v=vs.60).aspx
//
// If you are compiling a Windows DLL with constituent static libraries use
// -DMULLE_C_EXTERN_GLOBAL=extern. This ensures that global variables of those
// libraries are internally (within the DLL) linked.
//
// > Remember a DLL can't link with itself and the __imp_ stuff is generated
// > by the linker and is not available in the static LIBs
//
// Using -DMULLE_C_EXTERN_GLOBAL fails if your DLL links against other
// mulle_c11 derived dlls, because of conflicting settings. Therefore
// it's best to define and use your own package MULLE_C_EXTERN_GLOBAL
//
// e.g.
//    #ifndef MULLE_OBJC_EXTERN_GLOBAL
//      # define MULLE_OBJC_EXTERN_GLOBAL  MULLE_C_EXTERN_GLOBAL
//    #endif
// and override that with
// -DMULLE_OBJC_EXTERN_GLOBAL=extern
//
#ifdef _WIN32
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern  __declspec( dllimport)
# endif
# define MULLE_C_GLOBAL           __declspec( dllexport)
#else
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern
# endif
# define MULLE_C_GLOBAL
#endif

//
// stuff only clang and gcc understands
//
#if defined( __clang__) || defined( __GNUC__)

# define MULLE_C_ALWAYS_INLINE         __attribute__(( always_inline))
# define MULLE_C_NEVER_INLINE          __attribute__(( noinline))

# define MULLE_C_CONST_RETURN          __attribute__(( const))
# define MULLE_C_NO_RETURN             __attribute__(( noreturn))

# define MULLE_C_DEPRECATED            __attribute__(( deprecated))

// use these for function pointer modifiers (because win...)
# define _MULLE_C_NO_RETURN            MULLE_C_NO_RETURN
# define _MULLE_C_NEVER_INLINE         MULLE_C_NEVER_INLINE

#else

# ifdef _WIN32
#  define MULLE_C_NO_RETURN            __declspec( noreturn)
#  define MULLE_C_NEVER_INLINE         __declspec( noinline)

#  define _MULLE_C_NO_RETURN
#  define _MULLE_C_NEVER_INLINE

// check this https://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
// for MULLE_C_CONSTRUCTOR

# else
#  define MULLE_C_NO_RETURN
#  define MULLE_C_NEVER_INLINE
#  define _MULLE_C_NO_RETURN
#  define _MULLE_C_NEVER_INLINE
# endif

# define MULLE_C_ALWAYS_INLINE
# define MULLE_C_CONST_RETURN
# define MULLE_C_DEPRECATED

#endif

// clang only (?)
// gcc (at least < 4.8) doesn't like ‘returns_nonnull’ apparently ?

#if defined( __clang__)
# define MULLE_C_NONNULL_RETURN       __attribute__(( returns_nonnull))
#else
# define MULLE_C_NONNULL_RETURN
#endif


// some composites

#define MULLE_C_CONST_NONNULL_RETURN                 MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_CONST_RETURN

#define MULLE_C_ALWAYS_INLINE_NONNULL_RETURN         MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_ALWAYS_INLINE

#define MULLE_C_ALWAYS_INLINE_NONNULL_CONST_RETURN   MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_ALWAYS_INLINE \
                                                     MULLE_C_CONST_RETURN


//
// cross platform __attribute__((constructor))
// place in front of function w/o ;
// https://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
// Use C++ initialized. C (.CRT$XIU) doesn't work, I guess, because on windows
// it returns a value (possibly terminating) and we are void here.
//
// The underscore method is global and will conflict with other symbols!
//

#ifdef _MSC_VER
# pragma section(".CRT$XCU",read)
# define MULLE_C_CONSTRUCTOR2_( f, p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_"))
# ifdef _WIN64
#  define MULLE_C_CONSTRUCTOR( f) MULLE_C_CONSTRUCTOR2_(f,"")
# else
#  define MULLE_C_CONSTRUCTOR (f) MULLE_C_CONSTRUCTOR2_(f,"_")
# endif
#else
# define MULLE_C_CONSTRUCTOR( f) \
        __attribute__((constructor))
#endif


//
// cross platform __attribute__((destructor)). It's not really clear when and
// if this runs though. This is just compiler decl stuff.
//
// https://www.gonwan.com/2014/02/13/msvc-crt-initialization/
// ".CRT$XTU" is basically guessed
//
// Use XTU for "user" terminator C which is void:
// https://github.com/wyrover/book-code/blob/master/Linux%E4%B8%8B%E7%9A%84C%E5%BA%93%E5%87%BD%E6%95%B0%E6%BA%90%E4%BB%A3%E7%A0%81/%E6%9C%80%E5%85%A8%E7%9A%84Linux%E4%B8%8B%E7%9A%84C%E5%BA%93%E5%87%BD%E6%95%B0%E6%BA%90%E4%BB%A3%E7%A0%811/src/crt0dat.c
//
#ifdef _MSC_VER
# pragma section(".CRT$XTU",read)
# define MULLE_C_DESTRUCTOR2_( f, p) \
        static void f(void); \
        __declspec(allocate(".CRT$XTU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_"))
# ifdef _WIN64
#  define MULLE_C_DESTRUCTOR( f) MULLE_C_DESTRUCTOR2_(f,"")
# else
#  define MULLE_C_DESTRUCTOR( f) MULLE_C_DESTRUCTOR2_(f,"_")
# endif
#else
# define MULLE_C_DESTRUCTOR( f) \
        __attribute__((destructor))
#endif



//
// Some warnings are just too much for regular builds.
// Sometimes if one has a weird error it's nice to enable
// this though. So it is recommeded to compile with
// -DMULLE_C11_NO_NOOB_WARNINGS=1 by default
//
// The alternative would be to gum up the code...
//
#if MULLE_C11_NO_NOOB_WARNINGS

# if defined( __clang__)
// if( x = next()) , don't need that warning all the time
#  pragma clang diagnostic ignored "-Wparentheses"

// switch( enum), don't need missing case warning ever really
#  pragma clang diagnostic ignored "-Wswitch"

// That's what a category is good for...
#  pragma clang diagnostic ignored "-Wobjc-protocol-method-implementation"
# endif


# if defined( __GNUC__)
#  pragma GCC diagnostic ignored "-Wparentheses"
#  pragma GCC diagnostic ignored "-Wswitch"
#  pragma GCC diagnostic ignored "-Wobjc-protocol-method-implementation"
# endif

#endif


//
// mark functions arguments a nonnull. This will indicate that a null argument
// will make the the function crash. Nothing more, nothing less.
//
// For mulle code adorn only `_` prefixed functions with MULLE_C_NONNULL_.
// Non-prefixed functions must not crash on null input, consequently must check
// input parameters and then the MULLE_C_NONNULL_ is a hindrance.
//
// Add to these defines as desired. Remember, more than five arguments:
// wrap them into a struct!
//
#if defined( __clang__) || defined( __GNUC__)
# define MULLE_C_NONNULL_FIRST                __attribute__((nonnull(1)))
# define MULLE_C_NONNULL_FIRST_SECOND         __attribute__((nonnull(1,2)))
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD   __attribute__((nonnull(1,2,3)))
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH  __attribute__((nonnull(1,2,4)))
# define MULLE_C_NONNULL_FIRST_SECOND_FIFTH   __attribute__((nonnull(1,2,5)))
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH_FIFTH __attribute__((nonnull(1,2,4,5)))
# define MULLE_C_NONNULL_FIRST_THIRD          __attribute__((nonnull(1,3)))
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH   __attribute__((nonnull(3,4)))
# define MULLE_C_NONNULL_FIRST_FOURTH         __attribute__((nonnull(1,4)))
# define MULLE_C_NONNULL_FIRST_FIFTH          __attribute__((nonnull(1,5)))
# define MULLE_C_NONNULL_SECOND               __attribute__((nonnull(2)))
# define MULLE_C_NONNULL_SECOND_THIRD         __attribute__((nonnull(2,3)))
# define MULLE_C_NONNULL_THIRD                __attribute__((nonnull(3)))
# define MULLE_C_NONNULL_FOURTH               __attribute__((nonnull(4)))
# define MULLE_C_NONNULL_THIRD_FOURTH         __attribute__((nonnull(3,4)))
# define MULLE_C_NONNULL_FIFTH                __attribute__((nonnull(4)))
#else
# define MULLE_C_NONNULL_FIRST
# define MULLE_C_NONNULL_FIRST_SECOND
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH
# define MULLE_C_NONNULL_FIRST_SECOND_FIFTH
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIRST_THIRD
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH
# define MULLE_C_NONNULL_FIRST_FOURTH
# define MULLE_C_NONNULL_FIRST_FIFTH
# define MULLE_C_NONNULL_SECOND
# define MULLE_C_NONNULL_SECOND_THIRD
# define MULLE_C_NONNULL_THIRD
# define MULLE_C_NONNULL_THIRD_FOURTH
# define MULLE_C_NONNULL_FOURTH
# define MULLE_C_NONNULL_FIFTH
#endif

#endif // h
