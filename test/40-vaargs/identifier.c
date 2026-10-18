#include <stdio.h>
#include <string.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// The identifier expansion needs __VA_OPT__ (C23). Guarded, so this test also
// compiles and passes on a compiler without it.
//
#if MULLE_C_HAS_VA_OPT
# include <mulle-c11/mulle-c23-eval.h>

#define STRUCT_VALUE( expr, s) .s = expr

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
   const char   *identifier;

   identifier = MULLE_C_EVAL( MULLE_C_FOR_EACH_IDENTIFIER( STRUCT_VALUE,
                                                          1.0f,
                                                          "VfL Bochum",
                                                          1848LL));

   printf( "identifier = %s\n", identifier);
   return( strcmp( identifier, "viii") == 0 ? 0 : 1);
}

#else

int   main( void)
{
   return( 0);
}

#endif
