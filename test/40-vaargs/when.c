#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   MULLE_C_WHEN( 0)( printf( "0\n"); )
   MULLE_C_WHEN( 1)( printf( "1\n"); )

   return( 0);
}

