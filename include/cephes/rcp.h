/* SIMD SSE2 implementation of cephes

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library
*/

/* Copyright (C) 2009 Ralph Eastwood

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  (this is the zlib license)
*/

#ifndef _CEPHES_RCP_H_
#define _CEPHES_RCP_H_

#include "common.h"

static inline v4sf rcp_ps(v4sf x) {
  v4sf r = _mm_rcp_ps(x);
  r = _mm_sub_ps(_mm_add_ps(r, r), _mm_mul_ps(_mm_mul_ps(r, x), r));
  return r;
}

#endif /* _CEPHES_RCP_H_ */
