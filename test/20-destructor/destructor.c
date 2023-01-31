#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>
#include <stdio.h>


MULLE_C_DESTRUCTOR( unload)
static void  unload( void)
{
   printf( "%s\n", __FUNCTION__);
}


int   main( void)
{
   printf( "%s\n", __FUNCTION__);
   return( 0);
}

