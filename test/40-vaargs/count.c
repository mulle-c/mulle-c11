#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// MULLE_C_VA_ARGS_COUNT needs __VA_OPT__ (C23). The test is guarded, so it
// also compiles and passes on a compiler without it. Verification is done with
// compile time assertions, not a .stdout file, which could not match both.
//
#if MULLE_C_HAS_VA_OPT
# include <mulle-c11/mulle-c23-eval.h>
#endif


int   main( void)
{
#if MULLE_C_HAS_VA_OPT
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT() == 0, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1) == 1, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2) == 2, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3) == 3, "count");

   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4) == 4, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5) == 5, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6) == 6, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7) == 7, "count");

   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8) == 8, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9) == 9, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) == 10, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11) == 11, "count");

   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12) == 12, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13) == 13, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14) == 14, "count");
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15) == 15, "count");

   // also fifteen, you can't help it
   MULLE_C_ASSERT( MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) == 15, "count");
#endif

   return( 0);
}
