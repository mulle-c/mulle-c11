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
// Used to be in mulle-objc, but now it's here to be included on-demand
// not by default in the mulle-c11.h header.
//

#include <stddef.h>
#include <stdbool.h>

//
// having YES, NO as an enum messes up the boxed expressions @YES @NO
// but use @(YES) @(NO) and everything is fine
//
// TODO: an intptr_t would be wasteful in properties but would ease the
//       pain in metaabi calls. So this could turn into a typedef of NSInteger
//


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
// the hated BOOL. here it is an int
// on windows it unfortunately already exists in "minwindef.h" (when
// compiling with mingw)
// so don't typedef it
//
#if defined( _WIN32)
# ifndef _MINWINDEF_
//#  error "The #include <minwindef.h> is missing. Include <windows.h> somewhere."
# endif
#else
typedef enum _MulleBool   BOOL;
#endif

#endif
