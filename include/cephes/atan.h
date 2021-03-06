/* SIMD (SSE1+MMX or SSE2) implementation of cephes math library

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library

   The default is to use the SSE1 version. If you define USE_SSE2 the
   the SSE2 intrinsics will be used in place of the MMX intrinsics. Do
   not expect any significant performance improvement with SSE2.
*/

/* Copyright (C) 2009-2013 Ralph Eastwood

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

#ifndef _CEPHES_ATAN_H_
#define _CEPHES_ATAN_H_

#include "common.h"
#include "rcp.h"

static inline v4sf atan_ps(v4sf x) {
  v4sf xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
  v4sf y, z;
  v4sf sign_bit;
  
  sign_bit = x;
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  /* extract the sign bit (upper one) */
  sign_bit = _mm_and_ps(sign_bit, *(v4sf*)_ps_sign_mask);
  
  /* range reduction */
  xmm0 = _mm_cmpgt_ps(x, *(v4sf*)_ps_cephes_T3PIO8);
  xmm4 = _mm_cmpgt_ps(x, *(v4sf*)_ps_cephes_TPIO8);
  xmm1 = _mm_andnot_ps(xmm0, xmm4);
  y = _mm_and_ps(xmm0, *(v4sf*)_ps_cephes_PIO2F);
  y = _mm_or_ps(y, _mm_and_ps(xmm1, *(v4sf*)_ps_cephes_PIO4F));
  xmm5 = _mm_and_ps(xmm0, _mm_xor_ps(*(v4sf*)_ps_sign_mask, rcp_ps(x)));
  xmm2 = _mm_sub_ps(x, *(v4sf*)_ps_1);
  xmm3 = _mm_add_ps(x, *(v4sf*)_ps_1);
  xmm5 = _mm_or_ps(xmm5, _mm_and_ps(xmm1, _mm_mul_ps(xmm2, rcp_ps(xmm3))));
  x = _mm_or_ps(_mm_andnot_ps(xmm4, x), xmm5);
  z = _mm_mul_ps(x, x);
  
  xmm0 = _mm_mul_ps(*(v4sf*)_ps_atanf_p0, z);
  xmm1 = _mm_add_ps(*(v4sf*)_ps_atanf_p1, xmm0);
  xmm0 = _mm_mul_ps(xmm1, z);
  xmm1 = _mm_add_ps(*(v4sf*)_ps_atanf_p2, xmm0);
  xmm0 = _mm_mul_ps(xmm1, z);
  xmm1 = _mm_add_ps(*(v4sf*)_ps_atanf_p3, xmm0);
  xmm0 = _mm_mul_ps(xmm1, z);
  xmm0 = _mm_mul_ps(xmm0, x);
  xmm0 = _mm_add_ps(xmm0, x);
  y = _mm_add_ps(y, xmm0);
  
  return _mm_xor_ps(sign_bit, y);
}

static inline v4sf atan2_ps(v4sf y, v4sf x) {
  v4sf xmm0, xmm1, xmm2, xmm3;
  v4sf xmm4, xmm5, xmm6, xmm7;
  v4sf sign_bit;
  v4sf z, w;
  
  xmm0 = _mm_cmplt_ps(x, _mm_setzero_ps());
  xmm1 = _mm_cmplt_ps(y, _mm_setzero_ps());
  xmm2 = _mm_cmpeq_ps(x, _mm_setzero_ps());
  xmm3 = _mm_cmpeq_ps(y, _mm_setzero_ps());
  
  sign_bit = _mm_and_ps(xmm1, *(v4sf*)_ps_sign_mask);
  xmm5 = _mm_and_ps(xmm0, *(v4sf*)_ps_cephes_PI);
  w = _mm_or_ps(xmm5, sign_bit);
  z = atan_ps(_mm_mul_ps(y, rcp_ps(x)));
  xmm4 = _mm_add_ps(w, z);
  
  /* x == 0.0 */
  xmm6 = _mm_andnot_ps(xmm2, xmm4);
  xmm7 = _mm_andnot_ps(xmm1, *(v4sf*)_ps_cephes_PIO2F);
  xmm7 = _mm_or_ps(xmm7, sign_bit);
  xmm7 = _mm_andnot_ps(xmm3, xmm7);
  xmm7 = _mm_and_ps(xmm2, xmm7);
  xmm0 = _mm_or_ps(xmm6, xmm7);
  
  return xmm0;
}

static inline float atan_fast(float y, float x)
{
	float a, d, s, t;

	if (y > x) {
		a = -x / y;
		d = M_PI / 2;
	} else {
		a = y / x;
		d = 0.0f;
	}

	s = a * a;
	t = 0.0028662257f;
	t *= s;
	t += -0.0161657367f;
	t *= s;
	t += 0.0429096138f;
	t *= s;
	t += -0.0752896400f;
	t *= s;
	t += 0.1065626393f;
	t *= s;
	t += -0.1420889944f;
	t *= s;
	t += 0.1999355085f;
	t *= s;
	t += -0.3333314528f;
	t *= s;
	t += 1.0f;
	t *= a;
	t += d;

	return t;
}

#endif /* _CEPHES_ATAN_H_ */
