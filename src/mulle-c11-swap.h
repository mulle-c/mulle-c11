//
//  mulle-c11-endian.h
//  mulle-c11
//
//  Copyright © 2024 Mulle kybernetiK. All rights reserved.
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
#ifndef mulle_c11_swap_h__
#define mulle_c11_swap_h__

#include <stdint.h>


#pragma mark - base mulle swap functions

static inline uint16_t   mulle_swap_uint16( uint16_t value)
{
   return( (uint16_t) (value >> 8) | (uint16_t) (value << 8));
}


static inline uint32_t   mulle_swap_uint32( uint32_t value)
{
   return( mulle_swap_uint16( (uint16_t) (value >> 16)) |
          ((uint32_t) mulle_swap_uint16( (uint16_t) value) << 16));
}


static inline uint64_t   mulle_swap_uint64( uint64_t value)
{
   return( mulle_swap_uint32( (uint32_t) (value >> 32)) | 
          ((uint64_t) mulle_swap_uint32( (uint32_t) value) << 32));
}


static inline void   mulle_swap_10bytes( unsigned char bytes[ 10])
{
   unsigned char   c;

   c = bytes[ 0]; bytes[ 0] = bytes[ 9]; bytes[ 9] = c;
   c = bytes[ 1]; bytes[ 1] = bytes[ 8]; bytes[ 8] = c;
   c = bytes[ 2]; bytes[ 2] = bytes[ 7]; bytes[ 7] = c;
   c = bytes[ 3]; bytes[ 3] = bytes[ 6]; bytes[ 6] = c;
   c = bytes[ 4]; bytes[ 4] = bytes[ 5]; bytes[ 5] = c;
}


static inline uint16_t   mulle_big_uint16_to_host( uint16_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint16( value));
#endif
}


static inline uint32_t   mulle_big_uint32_to_host( uint32_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint32( value));
#endif
}


static inline uint64_t   mulle_big_uint64_to_host( uint64_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint64( value));
#endif
}


static inline uint16_t   mulle_host_uint16_to_big( uint16_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint16( value));
#endif
}


static inline uint32_t   mulle_host_uint32_to_big( uint32_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint32( value));
#endif
}


static inline uint64_t   mulle_host_uint64_to_big( uint64_t value)
{
#if __BIG_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint64( value));
#endif
}


static inline uint16_t   mulle_little_uint16_to_host( uint16_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint16( value));
#endif
}


static inline uint32_t   mulle_little_uint32_to_host( uint32_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint32( value));
#endif
}


static inline uint64_t   mulle_little_uint64_to_host( uint64_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint64( value));
#endif
}


static inline uint16_t   mulle_host_uint16_to_little( uint16_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint16( value));
#endif
}


static inline uint32_t   mulle_host_uint32_to_little( uint32_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint32( value));
#endif
}


static inline uint64_t   mulle_host_uint64_to_little( uint64_t value)
{
#if __LITTLE_ENDIAN__
   return( value);
#else
   return( mulle_swap_uint64( value));
#endif
}


#pragma mark - floating point types

typedef struct
{
   uint32_t   v;
} mulle_swapped_float;


typedef struct
{
   uint64_t   v;
} mulle_swapped_double;


typedef struct
{
   uint8_t   v[ 10];
} mulle_swapped_long_double;


union mulle_swapped_long_double_temp
{
   long double                ld;
   mulle_swapped_long_double  swapped;
};


union mulle_swapped_double_temp
{
   double                d;
   mulle_swapped_double  swapped;
};


union mulle_swapped_float_temp
{
   float               f;
   mulle_swapped_float swapped;
};


static inline mulle_swapped_float   mulle_host_float_to_swapped( float value)
{
   return( (union mulle_swapped_float_temp *) &value)->swapped;
}


static inline float   mulle_swapped_float_to_host( mulle_swapped_float value)
{
   return( (union mulle_swapped_float_temp *) &value)->f;
}


static inline mulle_swapped_double   mulle_host_double_to_swapped( double value)
{
   return( (union mulle_swapped_double_temp *) &value)->swapped;
}


static inline double   mulle_swapped_double_to_host( mulle_swapped_double value)
{
   return( (union mulle_swapped_double_temp *) &value)->d;
}


static inline mulle_swapped_long_double   mulle_host_long_double_to_swapped( long double value)
{
   return( (union mulle_swapped_long_double_temp *) &value)->swapped;
}


static inline long double   mulle_swapped_long_double_to_host( mulle_swapped_long_double value)
{
   return( (union mulle_swapped_long_double_temp *) &value)->ld;
}

#pragma mark - floating point swap operations

static inline mulle_swapped_float   mulle_swap_float( mulle_swapped_float value)
{
   value.v = mulle_swap_uint32( value.v);
   return( value);
}


static inline mulle_swapped_double   mulle_swap_double( mulle_swapped_double value)
{
   value.v = mulle_swap_uint64( value.v);
   return( value);
}


static inline mulle_swapped_long_double   mulle_swap_long_double( mulle_swapped_long_double value)
{
   mulle_swap_10bytes( value.v);
   return( value);
}


#if defined(__BIG_ENDIAN__)

static inline float   mulle_big_float_to_host( mulle_swapped_float value)
{
   return( mulle_swapped_float_to_host( value));
}


static inline double   mulle_big_double_to_host( mulle_swapped_double value)
{
   return( mulle_swapped_double_to_host( value));
}


static inline long double   mulle_big_long_double_to_host( mulle_swapped_long_double value)
{
   return( mulle_swapped_long_double_to_host( value));
}


static inline mulle_swapped_float   mulle_host_float_to_big( float value)
{
   return( mulle_host_float_to_swapped( value));
}


static inline mulle_swapped_double   mulle_host_double_to_big( double value)
{
   return( mulle_host_double_to_swapped( value));
}


static inline mulle_swapped_long_double   mulle_host_long_double_to_big( long double value)
{
   return( mulle_host_long_double_to_swapped( value));
}


static inline float   mulle_little_float_to_host( mulle_swapped_float value)
{
   return( mulle_swapped_float_to_host( mulle_swap_float( value)));
}


static inline double   mulle_little_double_to_host( mulle_swapped_double value)
{
   return( mulle_swapped_double_to_host( mulle_swap_double( value)));
}


static inline long double   mulle_little_long_double_to_host( mulle_swapped_long_double value)
{
   return( mulle_swapped_long_double_to_host( mulle_swap_long_double( value)));
}


static inline mulle_swapped_float   mulle_host_float_to_little( float value)
{
   return( mulle_swap_float( mulle_host_float_to_swapped( value)));
}


static inline mulle_swapped_double   mulle_host_double_to_little( double value)
{
   return( mulle_swap_double( mulle_host_double_to_swapped( value)));
}


static inline mulle_swapped_long_double   mulle_host_long_double_to_little( long double value)
{
   return( mulle_swap_long_double( mulle_host_long_double_to_swapped( value)));
}

#else

static inline float   mulle_big_float_to_host( mulle_swapped_float value)
{
   return( mulle_swapped_float_to_host( mulle_swap_float( value)));
}


static inline double   mulle_big_double_to_host( mulle_swapped_double value)
{
   return( mulle_swapped_double_to_host( mulle_swap_double( value)));
}


static inline long double   mulle_big_long_double_to_host( mulle_swapped_long_double value)
{
   return( mulle_swapped_long_double_to_host( mulle_swap_long_double( value)));
}


static inline mulle_swapped_float   mulle_host_float_to_big( float value)
{
   return( mulle_swap_float( mulle_host_float_to_swapped( value)));
}


static inline mulle_swapped_double   mulle_host_double_to_big( double value)
{
   return( mulle_swap_double( mulle_host_double_to_swapped( value)));
}


static inline mulle_swapped_long_double   mulle_host_long_double_to_big( long double value)
{
   return( mulle_swap_long_double( mulle_host_long_double_to_swapped( value)));
}


static inline float   mulle_little_float_to_host( mulle_swapped_float value)
{
   return( mulle_swapped_float_to_host( value));
}


static inline double   mulle_little_double_to_host( mulle_swapped_double value)
{
   return( mulle_swapped_double_to_host( value));
}


static inline long double   mulle_little_long_double_to_host( mulle_swapped_long_double value)
{
   return( mulle_swapped_long_double_to_host( value));
}


static inline mulle_swapped_float   mulle_host_float_to_little( float value)
{
   return( mulle_host_float_to_swapped( value));
}


static inline mulle_swapped_double   mulle_host_double_to_little( double value)
{
   return( mulle_host_double_to_swapped( value));
}


static inline mulle_swapped_long_double   mulle_host_long_double_to_little( long double value)
{
   return( mulle_host_long_double_to_swapped( value));
}

#endif


#endif
