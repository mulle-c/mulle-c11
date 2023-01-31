#include <mulle-c11/mulle-c11.h>

#include <stdio.h>


static inline void  egal( void)
{
   printf( "%s\n", __FUNCTION__);
}


int   main( void)
{
   egal(); // happy it it compiles and compiler can do it
   return( 0);
}

