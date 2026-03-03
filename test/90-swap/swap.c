#include "../src/mulle-c11-swap.h"
#include <stdio.h>
#include <assert.h>


static void   test_basic_swap( void)
{
   assert( mulle_swap_uint16( 0x1234) == 0x3412);
   assert( mulle_swap_uint32( 0x12345678) == 0x78563412);
   assert( mulle_swap_uint64( 0x123456789ABCDEF0ULL) == 0xF0DEBC9A78563412ULL);
}


static void   test_10bytes_swap( void)
{
   unsigned char   bytes[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   unsigned char   expected[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
   
   mulle_swap_10bytes( bytes);
   
   for( int i = 0; i < 10; i++)
      assert( bytes[i] == expected[i]);
}


static void   test_endian_conversions( void)
{
   uint16_t   val16 = 0x1234;
   uint32_t   val32 = 0x12345678;
   uint64_t   val64 = 0x123456789ABCDEF0ULL;
   
   // Round-trip tests work on any endianness
   assert( mulle_big_uint16_to_host( mulle_host_uint16_to_big( val16)) == val16);
   assert( mulle_little_uint16_to_host( mulle_host_uint16_to_little( val16)) == val16);
   
   assert( mulle_big_uint32_to_host( mulle_host_uint32_to_big( val32)) == val32);
   assert( mulle_little_uint32_to_host( mulle_host_uint32_to_little( val32)) == val32);
   
   assert( mulle_big_uint64_to_host( mulle_host_uint64_to_big( val64)) == val64);
   assert( mulle_little_uint64_to_host( mulle_host_uint64_to_little( val64)) == val64);
}


static void   test_float_swap( void)
{
   float   f = 1.5f;
   mulle_swapped_float   sf = mulle_host_float_to_swapped( f);
   
   assert( mulle_swapped_float_to_host( sf) == f);
   
   mulle_swapped_float   swapped = mulle_swap_float( sf);
   assert( swapped.v == mulle_swap_uint32( sf.v));
}


static void   test_double_swap( void)
{
   double   d = 2.5;
   mulle_swapped_double   sd = mulle_host_double_to_swapped( d);
   
   assert( mulle_swapped_double_to_host( sd) == d);
   
   mulle_swapped_double   swapped = mulle_swap_double( sd);
   assert( swapped.v == mulle_swap_uint64( sd.v));
}


static void   test_long_double_swap( void)
{
   long double   ld = 3.5L;
   mulle_swapped_long_double   sld = mulle_host_long_double_to_swapped( ld);
   
   assert( mulle_swapped_long_double_to_host( sld) == ld);
}


static void   test_float_endian( void)
{
   float   f = 1.5f;
   
   mulle_swapped_float   big = mulle_host_float_to_big( f);
   assert( mulle_big_float_to_host( big) == f);
   
   mulle_swapped_float   little = mulle_host_float_to_little( f);
   assert( mulle_little_float_to_host( little) == f);
}


int   main( void)
{
   test_basic_swap();
   test_10bytes_swap();
   test_endian_conversions();
   test_float_swap();
   test_double_swap();
   test_long_double_swap();
   test_float_endian();
   
   printf( "All swap tests passed\n");
   return( 0);
}
