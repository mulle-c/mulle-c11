#ifndef mulle_c11_h__
#define mulle_c11_h__

//
// basic C11 stuff, that's missing on some platforms
//
#ifdef _WIN32
# define alignof( x)  __alignof( x)
#else
# include <stdalign.h>
#endif

//
// stuff only clang and gcc understands
//
#if defined( __clang__) || defined( __GNUC__)
# define MULLE_C_ALWAYS_INLINE         __attribute__(( always_inline))
# define MULLE_C_CONST_VALUE_RETURN    __attribute__(( const))
#else
# define MULLE_C_ALWAYS_INLINE
# define MULLE_C_CONST_VALUE_RETURN
#endif

#endif
