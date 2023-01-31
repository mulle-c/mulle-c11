#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

#define MULLE_C_WHEN_NOT( c)         MULLE_C_IIF(c)( MULLE_C_EAT, MULLE_C_EXPAND)

#define _MULLE_C_FOR_EACH_IDENTIFIER( s, first, ...) \
    MULLE_C_WHEN( MULLE_C_HAS_ARGS(__VA_ARGS__)) \
    ( \
        MULLE_C_OBSTRUCT( __MULLE_C_FOR_EACH_IDENTIFIER) () \
        ( \
            s ## i, __VA_ARGS__ \
        ) \
    ) \
    MULLE_C_WHEN_NOT( MULLE_C_HAS_ARGS(__VA_ARGS__)) \
    ( \
      # s \
    )

#define __MULLE_C_FOR_EACH_IDENTIFIER() \
    _MULLE_C_FOR_EACH_IDENTIFIER

#define MULLE_C_FOR_EACH_IDENTIFIER( first, ...) \
    _MULLE_C_FOR_EACH_IDENTIFIER( v, first __VA_OPT__(,) __VA_ARGS__)



int   main( void)
{
   char   *s;
   printf( "identifier = %s\n",
      ( MULLE_C_EVAL( MULLE_C_FOR_EACH_IDENTIFIER( STRUCT_VALUE,  
                                                 1.0f, 
                                                 "VfL Bochum", 
                                                  1848LL)
                                     ))
   );

   return( 0);
}

