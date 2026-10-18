#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// The loop expansion needs __VA_OPT__ (C23). Guarded, so this test also
// compiles and passes on a compiler without it.
//
#if MULLE_C_HAS_VA_OPT
# include <mulle-c11/mulle-c23-eval.h>


#define LOOP( first, ...)                         \
   first                                          \
   MULLE_C_WHEN( MULLE_C_HAS_ARGS(__VA_ARGS__))   \
   (                                              \
      MULLE_C_OBSTRUCT( LOOP_INDIRECT) ()         \
      (                                           \
          __VA_ARGS__                             \
      )                                           \
   )                                              \

#define LOOP_INDIRECT()  LOOP


int   main( void)
{
   MULLE_C_EVAL( LOOP( printf( "a"); ));
   printf( "\n");
   MULLE_C_EVAL( LOOP( printf( "a"); , printf( "b"); ));
   printf( "\n");
   MULLE_C_EVAL( LOOP( printf( "a"); , printf( "b");, printf( "c"); ));
   printf( "\n");

   return( 0);
}

#else

int   main( void)
{
   return( 0);
}

#endif
