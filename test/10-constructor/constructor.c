#include <mulle-c11/mulle-c11.h>


#include <stdio.h>


MULLE_C_CONSTRUCTOR( load)
static void  load( void)
{
   printf( "%s\n", __FUNCTION__);
}


int   main( int argc, char *argv[])
{
   printf( "%s\n", __FUNCTION__);
   return( 0);
}

