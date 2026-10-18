#include <stdio.h>

#include <mulle-c11/mulle-c11.h>

//
// __typeof__ / MULLE_C_TYPE_OF is not C11. It is a GNU extension (C23 `typeof`).
// Guarded, so this test also compiles and passes on a compiler without it.
//
#if MULLE_C_HAS_TYPEOF
# include <mulle-c11/mulle-c23-feature.h>


int   main( void)
{
   int   x;
   int   y;

   MULLE_C_TYPE_OF( x)   value;
   MULLE_C_TYPE_OF( x)   *pointer;

   value   = 1848;
   pointer = &value;
   y       = x = 0;

   MULLE_C_ASSERT( sizeof( MULLE_C_TYPE_OF( x)) == sizeof( int), "typeof int");
   MULLE_C_ASSERT( sizeof( MULLE_C_TYPE_OF( pointer)) == sizeof( int *), "typeof pointer");

   printf( "value = %d\n", *pointer);
   return( (value == 1848 && y == 0) ? 0 : 1);
}

#else

int   main( void)
{
   return( 0);
}

#endif
