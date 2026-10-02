#include <mulle-c11/mulle-c11-builtin.h>

#include <stdio.h>
#include <assert.h>


static void   test_clz_uint32( void)
{
   int   i;

   assert( mulle_c_clz( 0x80000000U) == 0);
   assert( mulle_c_clz( 0x40000000U) == 1);
   assert( mulle_c_clz( 0x0000FFFFU) == 16);
   assert( mulle_c_clz( 0x00000001U) == 31);

   // single bit, anywhere in the word
   for( i = 0; i < 32; ++i)
      assert( mulle_c_clz( 1U << i) == 31 - i);

   // the sign bit is not special, this is not a signed shift
   assert( mulle_c_clz( 0xFFFFFFFFU) == 0);
}


static void   test_clz_ulong( void)
{
   // sizeof( unsigned long) differs between platforms, so these are the only
   // assertions that hold everywhere
   assert( mulle_c_clzl( 1UL) == (int) (sizeof( unsigned long) * 8) - 1);
   assert( mulle_c_clzl( ~0UL) == 0);
   assert( mulle_c_clzl( 0xFFFFUL) == (int) (sizeof( unsigned long) * 8) - 16);
}


static void   test_clz_uint64( void)
{
   int   i;

   assert( mulle_c_clzll( 0x8000000000000000ULL) == 0);
   assert( mulle_c_clzll( 0x0000000000000001ULL) == 63);
   assert( mulle_c_clzll( 0x00000000FFFFFFFFULL) == 32);
   assert( mulle_c_clzll( 0xCAFEBABE00000000ULL) == 0);

   for( i = 0; i < 64; ++i)
      assert( mulle_c_clzll( 1ULL << i) == 63 - i);
}


static void   test_log2_floor( void)
{
   int                  i;
   unsigned long long   value;

   // the one thing the clz builtins can't express
   assert( mulle_c_log2_floor( 0) == 0);
   assert( mulle_c_log2_floor( 1) == 0);
   assert( mulle_c_log2_floor( 2) == 1);
   assert( mulle_c_log2_floor( 3) == 1);
   assert( mulle_c_log2_floor( 63) == 5);
   assert( mulle_c_log2_floor( 64) == 6);

   // exact powers, and both neighbours of each. The neighbours only behave
   // as expected from 1 up, which the assertions above pin down for 0.
   for( i = 1; i < 64; ++i)
   {
      value = 1ULL << i;

      assert( mulle_c_log2_floor( value) == (unsigned int) i);
      assert( mulle_c_log2_floor( value + 1) == (unsigned int) i);
      assert( mulle_c_log2_floor( value - 1) == (unsigned int) (i - 1));
   }

   assert( mulle_c_log2_floor( 0xFFFFFFFFFFFFFFFFULL) == 63);
}


int   main( void)
{
   test_clz_uint32();
   test_clz_ulong();
   test_clz_uint64();
   test_log2_floor();

   printf( "All clz tests passed\n");
   return( 0);
}
