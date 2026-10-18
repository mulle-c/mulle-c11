#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// MULLE_C_HAS_ARGS needs __VA_OPT__ (C23). Guarded, so this test also compiles
// and passes on a compiler without it. Verification is compile time only.
//
#if MULLE_C_HAS_VA_OPT
# include <mulle-c11/mulle-c23-eval.h>
#endif


int   main( void)
{
#if MULLE_C_HAS_VA_OPT
   MULLE_C_ASSERT( MULLE_C_HAS_ARGS() == 0, "hasargs");
   MULLE_C_ASSERT( MULLE_C_HAS_ARGS(1) == 1, "hasargs");
   MULLE_C_ASSERT( MULLE_C_HAS_ARGS(1,2) == 1, "hasargs");
   MULLE_C_ASSERT( MULLE_C_HAS_ARGS(,) == 1, "hasargs");
#endif

   return( 0);
}
