//
//  mulle-c11-integer.h
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
#ifndef NSINTEGER_DEFINED
#define NSINTEGER_DEFINED

//
// Used to be in mulle-objc, but now it's here to be included on-demand
// not by default in the mulle-c11.h header.

#include <stdint.h>


// It's assumed that:
//
//    sizeof( ptrdiff_t) == sizeof( uintptr_t)
//    sizeof( uintptr_t) == sizeof( intptr_t)
//
// This is important for the mulle_printf '%td' formatting of NSInteger and
// then '%tu' formatting of NSUInteger, where actually sizeof( ptrdiff_t)
// is being used. The thing with ptrdiff_t is though, there is no unsigned
// variant AFAIK.
//
// asserted in _mulle_objc_universeconfiguration_configure_universe
//
typedef uintptr_t   NSUInteger;
typedef intptr_t    NSInteger;

#define NSIntegerMax    ((NSInteger) (((NSUInteger) -1) >> 1))
#define NSIntegerMin    (-((NSInteger) (((NSUInteger) -1) >> 1)) - 1)
#define NSUIntegerMax   ((NSUInteger) -1)
#define NSUIntegerMin   (0)


// not usually defined
static inline NSInteger   NSIntegerMaximum( NSInteger x, NSInteger y)
{
   return( x > y ? x : y);
}


static inline NSInteger   NSIntegerMinimum( NSInteger x, NSInteger y)
{
   return( x < y ? x : y);
}

#endif
