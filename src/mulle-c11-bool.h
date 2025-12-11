//
//  mulle-c11-bool.h
//  mulle-c11
//
//  Copyright © 2023 Mulle kybernetiK. All rights reserved.
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
#ifndef MULLE_BOOL_DEFINED
#define MULLE_BOOL_DEFINED


//
// having YES, NO as an enum messes up the boxed expressions @YES @NO
// but use @(YES) @(NO) and everything is fine
//
// TODO: an intptr_t would be wasteful in properties but would ease the
//       pain in metaabi calls. So this could turn into a typedef of NSInteger
//       except when its defined on windows already and we can't....


enum _MulleBool
{
   YES = 1,
   NO  = 0
};


static inline char   *_MulleBoolUTF8String( enum _MulleBool result)
{
   return( result ? "YES" : "NO");
}


//
// the hated BOOL. here it is an int on windows it unfortunately exists in 
// "minwindef.h" (when compiling with mingw at least):
// 
// #ifndef _DEF_WINBOOL_
// #define _DEF_WINBOOL_
// typedef int WINBOOL;
// #pragma push_macro("BOOL")
// #undef BOOL
// #if !defined(__OBJC__) && !defined(__OBJC_BOOL) && !defined(__objc_INCLUDE_GNU) && !defined(_NO_BOOL_TYPEDEF)
//   typedef int BOOL;
// #endif
// #define BOOL WINBOOL
// typedef BOOL *PBOOL;
// typedef BOOL *LPBOOL;
// #pragma pop_macro("BOOL")
// #endif /* _DEF_WINBOOL_ */
//
// so don't typedef it
//
#if defined( _WIN32)
# ifdef _DEF_WINBOOL_
#  error "you need to include <mulle-c11/mulle-c11-bool.h> before <windows.h> (specifically before <minwindef.h>"
# endif
# define _NO_BOOL_TYPEDEF  // possibly only MINGW
#endif

typedef enum _MulleBool   BOOL;

// i forgot why this was needed or desirable
#ifdef __has_include
# if __has_include(<stdbool.h>)
#  include <stdbool.h>
# endif
#endif

#endif
