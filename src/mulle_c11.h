#ifndef mulle_c11_h__
#define mulle_c11_h__

//
// basic C11 stuff, that's missing on some platforms
//
#ifdef _WIN32
# define alignof( x)  				__alignof( x)
# define __builtin_expect( x, y)	x
# define MULLE_C_EXTERN_GLOBAL		extern __declspec( dllimport)
#else
# include <stdalign.h>
# define MULLE_C_EXTERN_GLOBAL		extern
#endif

//
// stuff only clang and gcc understands
//
#if defined( __clang__) || defined( __GNUC__)

# define MULLE_C_ALWAYS_INLINE         __attribute__(( always_inline))
# define MULLE_C_NEVER_INLINE          __attribute__(( noinline))

# define MULLE_C_CONST_RETURN          __attribute__(( const))
# define MULLE_C_NO_RETURN             __attribute__(( noreturn))
# define MULLE_C_NON_NULL_RETURN       __attribute__(( returns_nonnull))

# define MULLE_C_CONSTRUCTOR           __attribute__(( constructor))

// some composites
# define MULLE_C_CONST_NON_NULL_RETURN                 __attribute__(( const, returns_nonnull))
# define MULLE_C_ALWAYS_INLINE_NON_NULL_RETURN         __attribute__(( always_inline, returns_nonnull))
# define MULLE_C_ALWAYS_INLINE_NON_NULL_CONST_RETURN   __attribute__(( always_inline, returns_nonnull, const))


#else


# define MULLE_C_ALWAYS_INLINE
# define MULLE_C_NEVER_INLINE

# define MULLE_C_CONST_RETURN
# define MULLE_C_NO_RETURN
# define MULLE_C_NON_NULL_RETURN

# define MULLE_C_CONSTRUCTOR

# define MULLE_C_CONST_NON_NULL_RETURN
# define MULLE_C_ALWAYS_INLINE_NON_NULL_RETURN
# define MULLE_C_ALWAYS_INLINE_NON_NULL_CONST_RETURN

#endif


#endif
