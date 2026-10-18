//
//  mulle-c23-feature.h
//  mulle-c11
//
//  Copyright (c) 2026 Nat! - Mulle kybernetiK.
//  All rights reserved.
//
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
#ifndef mulle_c23_feature_h__
#define mulle_c23_feature_h__


//
// C23 language features that gcc and clang already accept as an extension in
// earlier modes. This is the C23 counterpart to mulle-c11-feature.h: including
// it means "I am allowed to require C23 (or the gcc/clang extension)".
//
// The capability probes (MULLE_C_HAS_TYPEOF, ...) deliberately live in
// mulle-c11-feature.h, because a C11 consumer needs them to decide whether to
// pull this header in at all.
//
#include "mulle-c11-feature.h"

#if ! MULLE_C_HAS_TYPEOF
# error "mulle-c23-feature.h requires __typeof__ (C23), which this compiler does not have"
#endif


//
// __typeof__ is the reserved spelling of C23 `typeof`. It is understood by gcc
// and clang even in -std=c11 mode; guard optional use with MULLE_C_HAS_TYPEOF.
//
#define MULLE_C_TYPE_OF( expr)        __typeof__( expr)


#endif
