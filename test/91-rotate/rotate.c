#include <mulle-c11/mulle-c11-rotate.h>
#include <stdio.h>
#include <assert.h>


static void   test_rotate_right_uint32( void)
{
   // basic rotation
   assert( mulle_rotate_right_uint32( 0x12345678, 8) == 0x78123456);
   assert( mulle_rotate_right_uint32( 0x12345678, 16) == 0x56781234);
   assert( mulle_rotate_right_uint32( 0x12345678, 24) == 0x34567812);

   // zero shift is identity
   assert( mulle_rotate_right_uint32( 0x12345678, 0) == 0x12345678);

   // full rotation (32 & 31 == 0) is identity
   assert( mulle_rotate_right_uint32( 0x12345678, 32) == 0x12345678);

   // single bit
   assert( mulle_rotate_right_uint32( 0x00000001, 1) == 0x80000000);
   assert( mulle_rotate_right_uint32( 0x80000000, 1) == 0x40000000);

   // odd shifts
   assert( mulle_rotate_right_uint32( 0x12345678, 4) == 0x81234567);
}


static void   test_rotate_left_uint32( void)
{
   // basic rotation
   assert( mulle_rotate_left_uint32( 0x12345678, 8) == 0x34567812);
   assert( mulle_rotate_left_uint32( 0x12345678, 16) == 0x56781234);
   assert( mulle_rotate_left_uint32( 0x12345678, 24) == 0x78123456);

   // zero shift is identity
   assert( mulle_rotate_left_uint32( 0x12345678, 0) == 0x12345678);

   // full rotation is identity
   assert( mulle_rotate_left_uint32( 0x12345678, 32) == 0x12345678);

   // single bit
   assert( mulle_rotate_left_uint32( 0x80000000, 1) == 0x00000001);
   assert( mulle_rotate_left_uint32( 0x00000001, 1) == 0x00000002);

   // left and right are inverse
   assert( mulle_rotate_left_uint32( mulle_rotate_right_uint32( 0xDEADBEEF, 13), 13) == 0xDEADBEEF);
}


static void   test_rotate_right_uint64( void)
{
   assert( mulle_rotate_right_uint64( 0x123456789ABCDEF0ULL, 8) == 0xF0123456789ABCDEULL);
   assert( mulle_rotate_right_uint64( 0x123456789ABCDEF0ULL, 32) == 0x9ABCDEF012345678ULL);

   // zero shift is identity
   assert( mulle_rotate_right_uint64( 0x123456789ABCDEF0ULL, 0) == 0x123456789ABCDEF0ULL);

   // full rotation (64 & 63 == 0) is identity
   assert( mulle_rotate_right_uint64( 0x123456789ABCDEF0ULL, 64) == 0x123456789ABCDEF0ULL);

   // single bit
   assert( mulle_rotate_right_uint64( 0x0000000000000001ULL, 1) == 0x8000000000000000ULL);
}


static void   test_rotate_left_uint64( void)
{
   assert( mulle_rotate_left_uint64( 0x123456789ABCDEF0ULL, 8) == 0x3456789ABCDEF012ULL);
   assert( mulle_rotate_left_uint64( 0x123456789ABCDEF0ULL, 32) == 0x9ABCDEF012345678ULL);

   // zero shift is identity
   assert( mulle_rotate_left_uint64( 0x123456789ABCDEF0ULL, 0) == 0x123456789ABCDEF0ULL);

   // full rotation is identity
   assert( mulle_rotate_left_uint64( 0x123456789ABCDEF0ULL, 64) == 0x123456789ABCDEF0ULL);

   // single bit
   assert( mulle_rotate_left_uint64( 0x8000000000000000ULL, 1) == 0x0000000000000001ULL);

   // left and right are inverse
   assert( mulle_rotate_left_uint64( mulle_rotate_right_uint64( 0xDEADBEEFCAFEBABEULL, 37), 37) == 0xDEADBEEFCAFEBABEULL);
}


int   main( void)
{
   test_rotate_right_uint32();
   test_rotate_left_uint32();
   test_rotate_right_uint64();
   test_rotate_left_uint64();

   printf( "All rotate tests passed\n");
   return( 0);
}
