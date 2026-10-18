#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// Compiled with -DMULLE_C_HAS_VA_OPT=0 (see no-variadic.OTHER_CFLAGS) to
// verify that the C11-only path works: the probe is overridable and none of
// the __VA_OPT__ macros are pulled in.
//
int   main( void)
{
   MULLE_C_ASSERT( MULLE_C_HAS_VA_OPT == 0, "forced no __VA_OPT__");

   // plain C11 evaluation macros must still work
   printf( "%d\n", MULLE_C_VA_ARGS_2( 1, 2, 3));
   printf( "%d\n", MULLE_C_IIF( 1)( 4, 5));
   printf( "%d\n", MULLE_C_IIF( 0)( 4, 5));

   return( 0);
}
