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

#ifndef _CEPHES_ASIN_H_
#define _CEPHES_ASIN_H_

#include "common.h"
#include "sqrt.h"

static inline v4sf asin_ps(v4sf x) {
  v4sf xmm0, xmm1, xmm2;
  v4sf flag;
  v4sf z, z0;
  v4sf sign_bit;
  
  sign_bit = x;
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  /* extract the sign bit (upper one) */
  sign_bit = _mm_and_ps(sign_bit, *(v4sf*)_ps_sign_mask);
  
  flag = _mm_cmpgt_ps(x, *(v4sf*)_ps_0p5);
  xmm0 = _mm_mul_ps(*(v4sf*)_ps_0p5, _mm_sub_ps(*(v4sf*)_ps_1, x));
  //xmm2 = _mm_rcp_ps(_mm_rsqrt_ps(xmm0));
  //xmm2 = _mm_sqrt_ps(xmm0);
  xmm2 = sqrt_ps(xmm0);
  x = _mm_or_ps(_mm_and_ps(flag, xmm2), _mm_andnot_ps(flag, x));
  z0 = _mm_or_ps(_mm_and_ps(flag, xmm0), _mm_andnot_ps(flag, _mm_mul_ps(x, x)));
  
  z = _mm_mul_ps(z0, *(v4sf*)_ps_asinf_p0);
  z = _mm_add_ps(z, *(v4sf*)_ps_asinf_p1);
  z = _mm_mul_ps(z, z0);
  z = _mm_add_ps(z, *(v4sf*)_ps_asinf_p2);
  z = _mm_mul_ps(z, z0);
  z = _mm_add_ps(z, *(v4sf*)_ps_asinf_p3);
  z = _mm_mul_ps(z, z0);
  z = _mm_add_ps(z, *(v4sf*)_ps_asinf_p4);
  z = _mm_mul_ps(z, z0);
  z = _mm_mul_ps(z, x);
  z = _mm_add_ps(z, x);
  
  xmm1 = _mm_sub_ps( *(v4sf*)_ps_cephes_PIO2F, _mm_add_ps(z, z));
  z = _mm_or_ps(_mm_and_ps(flag, xmm1), _mm_andnot_ps(flag, z));
  
  return _mm_or_ps(sign_bit, z);
}

#endif /* _CEPHES_ASIN_H_ */
