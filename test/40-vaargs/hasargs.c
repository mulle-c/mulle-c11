#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   MULLE_C_WHEN( MULLE_C_HAS_ARGS())   ( printf( "0\n"); )  // won't print
   MULLE_C_WHEN( MULLE_C_HAS_ARGS(1))  ( printf( "1\n"); )
   MULLE_C_WHEN( MULLE_C_HAS_ARGS(1,2))( printf( "2\n"); )
   MULLE_C_WHEN( MULLE_C_HAS_ARGS(,))  ( printf( "3\n"); )

   return( 0);
}

