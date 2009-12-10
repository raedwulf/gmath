/* SIMD (SSE1+MMX or SSE2) implementation of sin, cos, exp and log

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library

   The default is to use the SSE1 version. If you define USE_SSE2 the
   the SSE2 intrinsics will be used in place of the MMX intrinsics. Do
   not expect any significant performance improvement with SSE2.
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

#ifndef _CEPHES_SQRT_H_
#define _CEPHES_SQRT_H_

#include "common.h"

v4sf sqrt_ps(v4sf x) {
  v4sf half = _mm_mul_ps(x, *(v4sf*)_ps_0p5);
  v4sf iszero = _mm_cmpeq_ps(_mm_setzero_ps(), x);
  v4sf x2 = _mm_rsqrt_ps(x);
  x2 = _mm_mul_ps(x2, _mm_sub_ps(*(v4sf*)_ps_1p5,
      _mm_mul_ps(half, _mm_mul_ps(x2, x2))));
  return _mm_andnot_ps(iszero, _mm_mul_ps(x2, x));
}

#endif /* _CEPHES_SQRT_H_ */
