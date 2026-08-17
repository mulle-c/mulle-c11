//
//  mulle-c11-rotate.h
//  mulle-c11
//
//  Copyright (c) 2026 Nat! - Mulle kybernetiK.
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
#ifndef mulle_c11_rotate_h__
#define mulle_c11_rotate_h__

#include <stdint.h>


//
// Portable rotate functions that compile to single ror/rol instructions
// on GCC and Clang with -O2. Uses the if-guard pattern to avoid undefined
// behavior when shift count is 0 or equals the type width.
//

static inline uint32_t   mulle_rotate_right_uint32( uint32_t value, unsigned shift)
{
   shift &= 31;
   if( shift)
      value = (value >> shift) | (value << (32 - shift));
   return( value);
}


static inline uint32_t   mulle_rotate_left_uint32( uint32_t value, unsigned shift)
{
   shift &= 31;
   if( shift)
      value = (value << shift) | (value >> (32 - shift));
   return( value);
}


static inline uint64_t   mulle_rotate_right_uint64( uint64_t value, unsigned shift)
{
   shift &= 63;
   if( shift)
      value = (value >> shift) | (value << (64 - shift));
   return( value);
}


static inline uint64_t   mulle_rotate_left_uint64( uint64_t value, unsigned shift)
{
   shift &= 63;
   if( shift)
      value = (value << shift) | (value >> (64 - shift));
   return( value);
}

#endif
