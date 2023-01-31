#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   char  *a = "a";
   char  *ab = "ab";
   char  *c = "c";

   printf( "%s\n", MULLE_C_CAT( a, ));
   printf( "%s\n", MULLE_C_CAT( a, b));

   // sic! b, c is emitted as is (separated by comma)
   printf( "%s%s\n", MULLE_C_CAT( a, b, c));

   return( 0);
}

