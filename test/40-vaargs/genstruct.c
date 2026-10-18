#include <stdio.h>
#include <string.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

//
// Needs __VA_OPT__ (MULLE_C_FOR_EACH) and __typeof__ (MULLE_C_TYPE_OF). Both
// are C23. Guarded, so this test also compiles and passes without them.
//
#if MULLE_C_HAS_VA_OPT && MULLE_C_HAS_TYPEOF
# include <mulle-c11/mulle-c23-eval.h>
# include <mulle-c11/mulle-c23-feature.h>


#define STRUCT_FIELD( expr, s) MULLE_C_TYPE_OF( expr)  s;
#define STRUCT_VALUE( expr, s) .s = expr

// STRUCT_FIELD( 1848, v)  -> int  v;
// STRUCT_VALUE( 1848, v)  -> .v = 1848;
// 
struct A
{
   MULLE_C_EVAL( MULLE_C_FOR_EACH( STRUCT_FIELD, 1.0f, "VfL Bochum", 1848LL))
};


int   main( void)
{
   struct A   a;

   a = (struct A) 
       { MULLE_C_EVAL( 
            MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR( STRUCT_VALUE,  
                                                   1.0f, 
                                                   "VfL Bochum", 
                                                   1848LL)
                     ) 
       };

   printf( "a.v = %g\n", a.v);
   printf( "a.vi = \"%s\"\n", a.vi);
   printf( "a.vii = %lldLL\n", a.vii);

   return( a.v == 1.0f
           && strcmp( a.vi, "VfL Bochum") == 0
           && a.vii == 1848LL ? 0 : 1);
}

#else

int   main( void)
{
   return( 0);
}

#endif
