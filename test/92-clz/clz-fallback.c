//
//  MULLE_C11_NO_BUILTINS compiles the portable implementations instead of the
//  builtins. Those are what run on a compiler without the builtins, so they
//  have to agree with them down to the last bit.
//
#define MULLE_C11_NO_BUILTINS

#include <mulle-c11/mulle-c11-builtin.h>

#include <stdio.h>
#include <assert.h>


int   main( void)
{
   int                  i;
   unsigned long long   value;

   for( i = 0; i < 32; ++i)
      assert( mulle_c_clz( 1U << i) == 31 - i);

   for( i = 0; i < 64; ++i)
   {
      assert( mulle_c_clzll( 1ULL << i) == 63 - i);

      value = 1ULL << i;
      assert( mulle_c_log2_floor( value) == (unsigned int) i);
      if( i)
         assert( mulle_c_log2_floor( value - 1) == (unsigned int) (i - 1));
   }

   // width of unsigned long is 32 on windows, 64 on linux
   assert( mulle_c_clzl( 1UL) == (int) (sizeof( unsigned long) * 8) - 1);
   assert( mulle_c_clzl( ~0UL) == 0);

   assert( mulle_c_log2_floor( 0) == 0);

   printf( "All clz fallback tests passed\n");
   return( 0);
}
