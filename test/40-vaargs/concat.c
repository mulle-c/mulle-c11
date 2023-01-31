#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   char  *a = "a";
   char  *ab = "ab";

   printf( "%s\n", MULLE_C_CONCAT( a, ));
   printf( "%s\n", MULLE_C_CONCAT( a, b));

   return( 0);
}

