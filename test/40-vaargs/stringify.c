#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   printf( "%s\n", MULLE_C_STRINGIFY());
   printf( "%s\n", MULLE_C_STRINGIFY( a));

   return( 0);
}

