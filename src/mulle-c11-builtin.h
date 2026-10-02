//
//  mulle-c11-builtin.h
//  mulle-c11
//
//  Copyright (c) 2026 Nat! - Mulle kybernetiK.
//  Copyright (c) 2016 Codeon GmbH.
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
#ifndef mulle_c11_builtin_h__
#define mulle_c11_builtin_h__

#include <stddef.h>

// __has_builtin is probed below and mulle-c11.h happens to include this file
// after mulle-c11-feature.h. Embedders that want only these functions include
// this header directly though, so get the fallback in place ourselves.
#include "mulle-c11-feature.h"

// useful builtin functions that are easy to re-implement
// with static inline functions
//
// Define MULLE_C11_NO_BUILTINS to get the reimplementations even where the
// builtins exist. That is how these fallbacks are tested (see test/92-clz),
// and it doubles as an escape hatch for a compiler whose builtin is broken.
//
#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_popcount)
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

#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_popcountl)
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


#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_popcountll)
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


// The count-leading-zeros builtins are all undefined for 0, as are these.
// If you want a defined answer for 0, use mulle_c_log2_floor.

#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_clz)
static inline int   mulle_c_clz( unsigned int bits)
{
   return( __builtin_clz( bits));
}
#else
static inline int   mulle_c_clz( unsigned int bits)
{
   unsigned int   n;

   n = 0;
   while( bits)
   {
      ++n;
      bits >>= 1;
   }
   return( (int) (sizeof( unsigned int) * 8 - n));
}
#endif


#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_clzl)
static inline int   mulle_c_clzl( unsigned long bits)
{
   return( __builtin_clzl( bits));
}
#else
static inline int   mulle_c_clzl( unsigned long bits)
{
   unsigned long   n;

   n = 0;
   while( bits)
   {
      ++n;
      bits >>= 1;
   }
   return( (int) (sizeof( unsigned long) * 8 - n));
}
#endif


#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_clzll)
static inline int   mulle_c_clzll( unsigned long long bits)
{
   return( __builtin_clzll( bits));
}
#else
static inline int   mulle_c_clzll( unsigned long long bits)
{
   unsigned long long   n;

   n = 0;
   while( bits)
   {
      ++n;
      bits >>= 1;
   }
   return( (int) (sizeof( unsigned long long) * 8 - n));
}
#endif


//
// floor( log2( bits)), defined for 0 as well, which answers 0. This is the
// useful derived function, as a bit index is rarely what you want and
// clamping the 0 case at every call site is noise.
//
static inline unsigned int   mulle_c_log2_floor( unsigned long long bits)
{
   if( ! bits)
      return( 0);
   return( (unsigned int) (sizeof( unsigned long long) * 8 - 1
                           - (unsigned int) mulle_c_clzll( bits)));
}


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



#if ! defined( MULLE_C11_NO_BUILTINS) && __has_builtin( __builtin_memcpy)
static inline void   mulle_c_memcpy( void *dst, const void *src, size_t n)
{
   __builtin_memcpy( dst, src, n);
}
#else
static inline void   mulle_c_memcpy( void *dst, const void *src, size_t n)
{
   extern void  *memcpy( void *dst, const void *src, size_t n);

   memcpy( dst, src, n);
}
#endif


#endif
