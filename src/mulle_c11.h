//
//  mulle_c11.h
//
//  Copyright © 2016 Mulle kybernetiK. All rights reserved.
//  Copyright © 2016 Codeon GmbH. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//

#ifndef mulle_c11_h__
#define mulle_c11_h__

#ifdef __cplusplus
# error "C++ ? You're doing it wrong."
#endif


//
// community version is always even
//
#define MULLE_C11_VERSION  ((1 << 20) | (1 << 8) | 1)


//
// basic C11 stuff, that's missing on "some" platforms
// https://gcc.gnu.org/wiki/C11Status
//
#ifndef MULLE_C11_NO_STDALIGN
# ifdef _WIN32
#  define MULLE_C11_NO_STDALIGN
# endif

# ifdef __GNUC__
#  if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)
#   define MULLE_C11_NO_STDALIGN
#  endif
# endif
#endif


#ifdef MULLE_C11_NO_STDALIGN
# define alignof( x)    __alignof( x)
#else
# include <stdalign.h>
#endif


#ifdef _WIN32
# define __builtin_expect( x, y) x
#endif


// if you are compiling a Windows DLL with constituent static libraries use
// -DMULLE_C_EXTERN_GLOBAL=extern. This ensures that global variables of those
// libraries are internally (within the DLL) linked.
//
// > Remember a DLL can't link with itself and the __imp_ stuff is generated
// > by the linker and is not available in the static LIBs
//
// Using -DMULLE_C_EXTERN_GLOBAL fails if your DLL links against other
// mulle_c11 derived dlls. Therefore it's best to define and use
// your own package MULLE_C_EXTERN_GLOBAL
// e.g.
//    #ifndef MULLE_OBJC_EXTERN_GLOBAL
//      # define MULLE_OBJC_EXTERN_GLOBAL  MULLE_C_EXTERN_GLOBAL
//    #endif
// and override that with
// -DMULLE_OBJC_EXTERN_GLOBAL=extern
//
#ifdef _WIN32
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern  __declspec( dllimport)
# endif
# define MULLE_C_GLOBAL           __declspec( dllexport)
#else
# ifndef MULLE_C_EXTERN_GLOBAL
#  define MULLE_C_EXTERN_GLOBAL   extern
# endif
# define MULLE_C_GLOBAL
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

# define MULLE_C_DEPRECATED           __attribute__(( deprecated))

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

# define MULLE_C_DEPRECATED

#endif

#endif
