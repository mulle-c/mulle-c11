#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


int   main( void)
{
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT());
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3));

   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7));

   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));

   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14));
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));

   // also fifteen, you can't help it
   printf( "%d\n", MULLE_C_VA_ARGS_COUNT( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));

   return( 0);
}

