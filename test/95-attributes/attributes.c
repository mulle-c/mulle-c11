#include "include.h"

#include <stdio.h>

//
// Every attribute in the "syntax and optimization" block of
// mulle-c11-feature.h must survive on a compiler that understands it.
// TinyCC understands all of them, but used to end up in the
// "no attributes at all" branch, which silently dropped them.
//
#if defined( __clang__) || defined( __GNUC__) || defined( __TINYC__)

static void   print_attribute( char *name, char *text)
{
   printf( "%-32s %s\n", name, *text ? "present" : "MISSING");
}


//
// weak must link even when the symbol is absent, so `if( f)` works
//
MULLE_C_WEAK int   this_symbol_does_not_exist( void);


int   main( void)
{
   print_attribute( "MULLE_C_WEAK",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_WEAK));
   print_attribute( "MULLE_C_STATIC_ALWAYS_INLINE",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_STATIC_ALWAYS_INLINE));
   print_attribute( "MULLE_C_ALWAYS_INLINE",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_ALWAYS_INLINE));
   print_attribute( "MULLE_C_NEVER_INLINE",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_NEVER_INLINE));
   print_attribute( "MULLE_C_NO_INSTRUMENT_FUNCTION",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_NO_INSTRUMENT_FUNCTION));
   print_attribute( "MULLE_C_CONST_RETURN",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_CONST_RETURN));
   print_attribute( "MULLE_C_NO_RETURN",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_NO_RETURN));
   print_attribute( "MULLE_C_DEPRECATED",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_DEPRECATED));
   print_attribute( "MULLE_C_FALLTHROUGH",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_FALLTHROUGH));
   print_attribute( "MULLE_C_UNUSED_FUNCTION",
                    MULLE_C_STRINGIFY_MACRO( MULLE_C_UNUSED_FUNCTION));
   print_attribute( "_MULLE_C_NO_RETURN",
                    MULLE_C_STRINGIFY_MACRO( _MULLE_C_NO_RETURN));
   print_attribute( "_MULLE_C_NEVER_INLINE",
                    MULLE_C_STRINGIFY_MACRO( _MULLE_C_NEVER_INLINE));

   printf( "%-32s %s\n",
           "weak absent symbol",
           this_symbol_does_not_exist ? "defined" : "absent");

   return( 0);
}

#else

int   main( void)
{
   printf( "unsupported compiler\n");
   return( 0);
}

#endif
