#include <stdio.h>
#include <stdarg.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>


void  print_nrs( int nr, ...)
{
   va_list  va;
   char     *sep;

   sep = "";

   va_start( va, nr);
   while( (nr = va_arg( va, int)) >= 0)
   {
      printf( "%s%d", sep, nr);
      sep = ", ";
   }
   va_end( va);

   printf( "\n");
}


int   main( void)
{
   print_nrs( 0xFEAD, MULLE_C_VA_ARGS_0(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xFEAD, MULLE_C_VA_ARGS_1(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xFEAD, MULLE_C_VA_ARGS_2(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xFEAD, MULLE_C_VA_ARGS_3(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);

   print_nrs( 0xDEAF, MULLE_C_VA_ARGS_4(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAF, MULLE_C_VA_ARGS_5(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAF, MULLE_C_VA_ARGS_6(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAF, MULLE_C_VA_ARGS_7(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);

   print_nrs( 0xDAD1, MULLE_C_VA_ARGS_8(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDAD1, MULLE_C_VA_ARGS_9(  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDAD1, MULLE_C_VA_ARGS_10( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDAD1, MULLE_C_VA_ARGS_11( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);

   print_nrs( 0xDEAD, MULLE_C_VA_ARGS_12( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAD, MULLE_C_VA_ARGS_13( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAD, MULLE_C_VA_ARGS_14( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);
   print_nrs( 0xDEAD, MULLE_C_VA_ARGS_15( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), -1);

   return( 0);
}

