#include <mulle-c11/mulle-c11.h>

#include <stdio.h>



int   main( void)
{
   int   values[ 3];
   void  *p = values;

   *mulle_c_pointer_postincrement( p, int) = 0x12;
   *mulle_c_pointer_postincrement( p, int) = 0x34;
   *mulle_c_pointer_postincrement( p, int) = 0x56;

   printf( "%x%x%x\n", values[ 0], values[ 1], values[ 2]);

   return( 0);
}

