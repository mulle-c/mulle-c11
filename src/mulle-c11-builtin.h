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

#ifndef mulle_c11_builtin_h__
#define mulle_c11_builtin_h__

#include <stddef.h>

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



#if __has_builtin( __builtin_memcpy)
static inline void   mulle_c_memcpy( void *dst, const void *src, size_t n)
{
   __builtin_memcpy( dst, src, n);
}
#else
static inline void   mulle_c_memcpy( void *dst, const void *src, size_t n)
{
   extern void   memcpy( void *dst, const void *src, size_t n);

   memcpy( dst, src, n);
}
#endif


#endif
