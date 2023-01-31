#include <mulle-c11/mulle-c11.h>


int   main( void)
{
   MULLE_C_ASSERT( sizeof( char) < sizeof( int), "this is OK");
   return( 0);
}

