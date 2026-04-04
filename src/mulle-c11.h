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


#define MULLE__C11_VERSION  ((4UL << 20) | (8 << 8) | 0)

#include "mulle-c11-feature.h"

// this needs to be ahead of any #include <windows.h>
#include "mulle-c11-bool.h"

// this wants to be ahead of any <windows.h> which mulle-c11-integer might do
#include "mulle-c11-endian.h"

#include "mulle-c11-integer.h"

#include "mulle-c11-builtin.h"

// these are too rearely used to want to be seen everywhere
// include them directly or define MULLE_C11_INCLUDE_ALL
#ifdef MULLE_C11_INCLUDE_ALL
# include "mulle-c11-align.h"
# include "mulle-c11-eval.h"
# include "mulle-c11-swap.h"
#endif

#endif
