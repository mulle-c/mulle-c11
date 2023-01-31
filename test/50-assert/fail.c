#include <mulle-c11/mulle-c11.h>


int   main( void)
{
   MULLE_C_ASSERT( sizeof( char) > sizeof( int), "this is very wrong");
   return( 0);
}

