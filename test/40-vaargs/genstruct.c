#include <stdio.h>

#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>



#define STRUCT_FIELD( expr, s) __typeof__( expr)  s;
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

   return( 0);
}

