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

// MEMO: THIS FILE MUST NOT INCLUDE ANYTHING

#ifdef __cplusplus
# error "C++ ? You're doing it wrong."
#endif


#ifndef __has_feature          // Optional.
# define __has_feature( x) 0   // Compatibility with non-clang compilers.
#endif

#ifndef __has_attribute
# define __has_attribute( x) 0
#endif

#ifndef __has_builtin
# define __has_builtin( x) 0
#endif



#define MULLE__C11_VERSION  ((4UL << 20) | (6 << 8) | 1)


//
// basic C11 stuff, that's missing on "some" platforms
// https://gcc.gnu.org/wiki/C11Status
//
#ifndef MULLE_C11_NO_STDALIGN
# ifdef _WIN32
#  define MULLE_C11_NO_STDALIGN 2
# endif

// to get to __COSMOPOLITAN__ we need to have included "cosmopolitan.h"
// before, which we can't guarantee. So the mulle-gcc.cosmopolitan
// compiler defines __MULLE_COSMOPOLITAN__ for use
# if defined( __COSMOPOLITAN__) || defined( __MULLE_COSMOPOLITAN__)
#  define MULLE_C11_NO_STDALIGN 1
# endif

# ifndef __clang__
#  ifdef __GNUC__
#   if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)
#    define MULLE_C11_NO_STDALIGN 2
#   endif
#  endif
# endif
#endif

#define MULLE_C_UNUSED( x)  ((void)(x))


#ifdef _WIN32
# define __builtin_expect( x, y) x
#endif

// ## Syntax and Optimization attributes
// stuff only clang and gcc understands, these attributes must not change
// symbol output (like weak does) for cross compilation use another batch
// of definitons (see above)
//
#if defined( __clang__) || defined( __GNUC__)

# define MULLE_C_STATIC_ALWAYS_INLINE  static inline  __attribute__(( always_inline))
# define MULLE_C_ALWAYS_INLINE         __attribute__(( always_inline))
# define MULLE_C_NEVER_INLINE          __attribute__(( noinline))
// uses for __cyg_profile_func_enter and __cyg_profile_func_leave
# define MULLE_C_NO_INSTRUMENT_FUNCTION __attribute__(( no_instrument_function))

# define MULLE_C_CONST_RETURN          __attribute__(( const))
# define MULLE_C_NO_RETURN             __attribute__(( noreturn))

# define MULLE_C_DEPRECATED            __attribute__(( deprecated))

# define MULLE_C_FALLTHROUGH           __attribute__(( fallthrough))

// use these for function pointer modifiers (because win...)
# define _MULLE_C_NO_RETURN            MULLE_C_NO_RETURN
# define _MULLE_C_NEVER_INLINE         MULLE_C_NEVER_INLINE

#else

# ifdef _WIN32

#  define MULLE_C_NO_RETURN            __declspec( noreturn)
#  define MULLE_C_NEVER_INLINE         __declspec( noinline)

#  define MULLE_C_STATIC_ALWAYS_INLINE static __forceinline

#  define MULLE_C_ALWAYS_INLINE        __forceinline
#  define MULLE_C_FALLTHROUGH          __fallthrough

// check this https://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
// for MULLE_C_CONSTRUCTOR

# else

#  define MULLE_C_NO_RETURN
#  define MULLE_C_NEVER_INLINE
#  define MULLE_C_ALWAYS_INLINE
#  define MULLE_C_STATIC_ALWAYS_INLINE   static inline
#  define MULLE_C_FALLTHROUGH
# endif

# define MULLE_C_NO_INSTRUMENT_FUNCTION
# define MULLE_C_CONST_RETURN
# define MULLE_C_DEPRECATED

# define _MULLE_C_NO_RETURN
# define _MULLE_C_NEVER_INLINE

#endif


#if defined( __clang__) || defined( __GNUC__) || defined( _WIN32)

# define MULLE_C_LIKELY( expr)         __builtin_expect( (expr), 1)
# define MULLE_C_UNLIKELY( expr)       __builtin_expect( (expr), 0)
# define MULLE_C_EXPECT( expr, value)  __builtin_expect( (expr), value)

#else

# define MULLE_C_LIKELY( expr)         (expr)
# define MULLE_C_UNLIKELY( expr)       (expr)
# define MULLE_C_EXPECT( expr, value)  (expr)

#endif


// clang only (?)
// gcc (at least < 4.8) doesn't like ‘returns_nonnull’ apparently ?

#if defined( __clang__)
# define MULLE_C_NONNULL_RETURN       __attribute__(( returns_nonnull))
#else
# define MULLE_C_NONNULL_RETURN
#endif


// some composites (soon to be deprecated)

#define MULLE_C_CONST_NONNULL_RETURN                 MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_CONST_RETURN

#define MULLE_C_ALWAYS_INLINE_NONNULL_RETURN         MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_ALWAYS_INLINE

#define MULLE_C_ALWAYS_INLINE_NONNULL_CONST_RETURN   MULLE_C_NONNULL_RETURN \
                                                     MULLE_C_ALWAYS_INLINE \
                                                     MULLE_C_CONST_RETURN

// ## Linker and Symbol attributes
//
// ### DLL Export/Import Mechanics (MSVC)
// 
// #### 1. **`__declspec(dllexport)`**
// 
// * **Exports a symbol** (e.g., `foo`) from a DLL.
// * Creates a corresponding **import symbol** (`__imp_foo`), which is used by other code that links to the DLL.
// * The **DLL contains the real function symbol** (`foo`), while the **import library (.lib)** contains a reference to `__imp_foo`.
// * The **Import Address Table (IAT)** is created when the DLL is loaded, holding the address of `foo`.
// 
// #### 2. **`__declspec(dllimport)`**
// 
// * **Imports a symbol** (e.g., `foo`) from a DLL.
// * Causes the compiler to **generate indirection** through `__imp_foo` (IAT entry) instead of directly calling `foo`.
// * The import does not “choose” between symbols but makes calls indirect.
// 
// #### 3. **What Happens with `p = &foo`**
// 
// * **Inside the DLL**: `foo` is a real function, so `&foo` directly points to its address in the DLL.
// * **Outside the DLL** (in client code): `&foo` refers to `__imp_foo`, which is an IAT pointer. The loader resolves this at runtime to the actual address of `foo` in the DLL.
// 
// #### 4. **Static Library vs DLL**
// 
// * **DLL**: Symbols are exported with `__declspec(dllexport)` and imported with `__declspec(dllimport)`. The IAT provides runtime resolution.
// * **Static Library**: Symbols are linked **statically** at compile time. There’s no runtime indirection or IAT; the function addresses are resolved directly.
// 
// #### 5. **Dual-use DLL/Static Library**
// 
// * For code that may be **both a DLL and a static library**, use a conditional macro:
// 
//   ```cpp
//   #ifdef BUILDING_DLL
//   #define API __declspec(dllexport)
//   #else
//   #define API __declspec(dllimport)
//   #endif
//   ```
// * This ensures proper symbol linkage whether the code is being compiled as a DLL or linked as a static library.
// 
// #### 6. **Linker Behavior**
// 
// * **DLL**: The import library contains references to `__imp_foo`. At runtime, the loader resolves `__imp_foo` to the actual function `foo` in the DLL.
// * **Static Library**: The `.lib` directly resolves symbols to their actual code (no IAT, no indirection).
// ---
// See research/dll:    
//
// `__declspec(dllexport)` in static libraries is harmlesss
// If you use `__declspec(dllimport)` in static code though, the compiler 
// will expect dynamic linking (bad).
// For dual-use libraries, always conditionally define the import/export macros 
// to handle both static and dynamic linking scenarios like so:
//
// ```c
// #ifdef BUILDING_DLL
//   #ifdef _WIN32
//     #define API __declspec(dllexport)
//   #else
//     #define API __attribute__((visibility("default")))
//   #endif
// #elif defined(USING_DLL)
//   #ifdef _WIN32
//     #define API __declspec(dllimport)
//   #else
//     #define API
//   #endif
// #else
//   #define API
// #endif
// ```
// ---
// The header can't know on its own, if its being used 
// * from the inside as a static library (no declspec wanted)
// * from the inside as a dynamic library declspec((export))
// * from the outside as a static library
// * from the outside as a dynamic library declspec((import))
//
// https://msdn.microsoft.com/en-us/library/aa271769(v=vs.60).aspx
//
// If you are compiling a Windows DLL with constituent static libraries use
// -DMULLE_C_EXTERN_GLOBAL=extern. This ensures that global variables of those
// libraries are internally (within the DLL) linked.
//
// Why is everything extern ? You need this for variables, which would be
// redefined. For functions it doesn't matter if there is an extern 
// keyword or not.
//
// Bottomline: In the .c file, you don't need to use __declspec only in .h.
//                                                     
#ifdef _WIN32
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern __declspec( dllimport)
# endif
# define MULLE_C_GLOBAL           extern __declspec( dllexport)
# define MULLE_C_WEAK            
#else
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern
# endif
# if defined( __clang__) || defined( __GNUC__)
#  define MULLE_C_GLOBAL          extern __attribute__(( visibility( "default")))
#  define MULLE_C_WEAK            __attribute__(( weak))
# else
#  define MULLE_C_GLOBAL          extern
#  define MULLE_C_WEAK            
# endif
#endif

// For rendezvous functions, it must be ascertained that the actual symbol
// is STATICALLY linked to the executable. Then MULLE_C_EXTERN_GLOBAL should
// not be used but just.
#define MULLE_C_RENDEZVOUS_SYMBOL            MULLE_C_GLOBAL  // MULLE_C_RENDEZVOUS_SYMBOL must not be declared in a dynamic compiled library 
#define MULLE_C_EXTERN_RENDEZVOUS_SYMBOL     MULLE_C_WEAK    

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
#  define MULLE_C_CONSTRUCTOR( f) MULLE_C_CONSTRUCTOR2_(f,"_")
# endif
#else
# define MULLE_C_CONSTRUCTOR( f) \
        __attribute__((constructor))
#endif


//
// This doesn't work on windows, if the CRT is linked as a DLL.
// I don't really need it on windows though, because atexit works there.
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
// #  pragma GCC diagnostic ignored "-Wobjc-protocol-method-implementation"
# endif

#endif


//
// Mark functions arguments a nonnull. This will indicate that a null argument
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
# define MULLE_C_NONNULL_FIRST                            __attribute__((nonnull(1)))
# define MULLE_C_NONNULL_FIRST_SECOND                     __attribute__((nonnull(1,2)))
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD               __attribute__((nonnull(1,2,3)))
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FOURTH        __attribute__((nonnull(1,2,3,4)))
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FOURTH_FIFTH  __attribute__((nonnull(1,2,3,4,5)))
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FIFTH         __attribute__((nonnull(1,2,3,5)))
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH              __attribute__((nonnull(1,2,4)))
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH_FIFTH        __attribute__((nonnull(1,2,4,5)))
# define MULLE_C_NONNULL_FIRST_SECOND_FIFTH               __attribute__((nonnull(1,2,5)))
# define MULLE_C_NONNULL_FIRST_THIRD                      __attribute__((nonnull(1,3)))
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH               __attribute__((nonnull(1,3,4)))
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH_FIFTH         __attribute__((nonnull(1,3,4,5)))
# define MULLE_C_NONNULL_FIRST_THIRD_FIFTH                __attribute__((nonnull(1,3,5)))
# define MULLE_C_NONNULL_FIRST_FOURTH                     __attribute__((nonnull(1,4)))
# define MULLE_C_NONNULL_FIRST_FOURTH_FIFTH               __attribute__((nonnull(1,4,5)))
# define MULLE_C_NONNULL_FIRST_FIFTH                      __attribute__((nonnull(1,5)))
# define MULLE_C_NONNULL_SECOND                           __attribute__((nonnull(2)))
# define MULLE_C_NONNULL_SECOND_THIRD                     __attribute__((nonnull(2,3)))
# define MULLE_C_NONNULL_SECOND_THIRD_FOURTH              __attribute__((nonnull(2,3,4)))
# define MULLE_C_NONNULL_SECOND_THIRD_FOURTH_FIFTH        __attribute__((nonnull(2,3,4,5)))
# define MULLE_C_NONNULL_SECOND_THIRD_FIFTH               __attribute__((nonnull(2,3,5)))
# define MULLE_C_NONNULL_SECOND_FOURTH                    __attribute__((nonnull(2,4)))
# define MULLE_C_NONNULL_SECOND_FOURTH_FIFTH              __attribute__((nonnull(2,4,5)))
# define MULLE_C_NONNULL_SECOND_FIFTH                     __attribute__((nonnull(2,5)))
# define MULLE_C_NONNULL_THIRD                            __attribute__((nonnull(3)))
# define MULLE_C_NONNULL_THIRD_FOURTH                     __attribute__((nonnull(3,4)))
# define MULLE_C_NONNULL_THIRD_FOURTH_FIFTH               __attribute__((nonnull(3,4,5)))
# define MULLE_C_NONNULL_THIRD_FIFTH                      __attribute__((nonnull(3,5)))
# define MULLE_C_NONNULL_FOURTH                           __attribute__((nonnull(4)))
# define MULLE_C_NONNULL_FOURTH_FIFTH                     __attribute__((nonnull(4,5)))
# define MULLE_C_NONNULL_FIFTH                            __attribute__((nonnull(5)))
#else
# define MULLE_C_NONNULL_FIRST
# define MULLE_C_NONNULL_FIRST_SECOND
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FOURTH
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIRST_SECOND_THIRD_FIFTH
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH
# define MULLE_C_NONNULL_FIRST_SECOND_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIRST_SECOND_FIFTH
# define MULLE_C_NONNULL_FIRST_THIRD
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH
# define MULLE_C_NONNULL_FIRST_THIRD_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIRST_THIRD_FIFTH
# define MULLE_C_NONNULL_FIRST_FOURTH
# define MULLE_C_NONNULL_FIRST_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIRST_FIFTH
# define MULLE_C_NONNULL_SECOND
# define MULLE_C_NONNULL_SECOND_THIRD
# define MULLE_C_NONNULL_SECOND_THIRD_FOURTH
# define MULLE_C_NONNULL_SECOND_THIRD_FOURTH_FIFTH
# define MULLE_C_NONNULL_SECOND_THIRD_FIFTH
# define MULLE_C_NONNULL_SECOND_FOURTH
# define MULLE_C_NONNULL_SECOND_FOURTH_FIFTH
# define MULLE_C_NONNULL_SECOND_FIFTH
# define MULLE_C_NONNULL_THIRD
# define MULLE_C_NONNULL_THIRD_FOURTH
# define MULLE_C_NONNULL_THIRD_FOURTH_FIFTH
# define MULLE_C_NONNULL_THIRD_FIFTH
# define MULLE_C_NONNULL_FOURTH
# define MULLE_C_NONNULL_FOURTH_FIFTH
# define MULLE_C_NONNULL_FIFTH
#endif

#define MULLE_C_STRINGIFY_MACRO( a)   MULLE_C_STRINGIFY( a)
#define MULLE_C_STRINGIFY( a)         #a
#define MULLE_C_CONCAT( a, b)         a ## b

//
// this is a compile time assert
// stolen from linux kernel BUG_ON and then modified somewhat
// You can add some text after the 'e' and hope it shows up in the compiler
// error message backtrace, or just leave it out
//
#ifndef NDEBUG
# define MULLE_C_ASSERT( e, ...)   ((void) ((struct { int:-!(e); char *s;}){ 0 }))
#else
# define MULLE_C_ASSERT( e, ...)
#endif


// useful builtin functions that are easy to re-implement
// with static inline functions

#if __has_builtin( __builtin_popcount)
static inline int   mulle_c_popcount( unsigned int bits)
{
   return( __builtin_popcount( bits));
}
#else
static inline int   mulle_c_popcount( unsigned int bits)
{
   int   n;

   n = 0;
   while( bits)
   {
      n     += bits & 1;
      bits >>= 1;
   }
   return( n);
}
#endif

#if __has_builtin( __builtin_popcountl)
static inline int   mulle_c_popcountl( unsigned long bits)
{
   return( __builtin_popcountl( bits));
}
#else
static inline int   mulle_c_popcountl( unsigned long bits)
{
   int   n;

   n = 0;
   while( bits)
   {
      n     += bits & 1;
      bits >>= 1;
   }
   return( n);
}
#endif


#if __has_builtin( __builtin_popcountll)
static inline int   mulle_c_popcountll( unsigned long long bits)
{
   return( __builtin_popcountll( bits));
}
#else
static inline int   mulle_c_popcountll( unsigned long long bits)
{
   int   n;

   n = 0;
   while( bits)
   {
      n     += bits & 1;
      bits >>= 1;
   }
   return( n);
}
#endif


//
// substitute mulle_c_pointer_postincrement( p, double)
// for code like *((double *) p)++
// which some language lawyer killed as invalid from the C language
//
// void *demo(void * num)
// {
//     *mulle_c_pointer_postincrement( num, int) = 1848;
//     return( num);
// }
//
// compiles down to (-O):
//
// demo(void*):
//         mov     DWORD PTR [rdi], 1848
//         lea     rax, [rdi+4]
//         ret
//
#define mulle_c_pointer_postincrement( p, type) \
   (p = (void *) &((char *) p)[ sizeof( type)], \
    (type *) &((char *) p)[ - (int) sizeof( type)])

#define mulle_c_pointer_predecrement( p, type) \
   ((type *) (p = (void *) &((char *) p)[ - (int) sizeof( type)]))


#endif
