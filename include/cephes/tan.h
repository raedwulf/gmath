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

#ifndef _CEPHES_TAN_H_
#define _CEPHES_TAN_H_

#include "common.h"
#include "rcp.h"

static inline v4sf tan_ps(v4sf x) {
  v4sf xmm0, xmm1;
  v4sf flag;
  v4si j, emm0;
  v4sf y, z, zz;
  v4sf sign_bit;
  
  sign_bit = x;
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  /* extract the sign bit (upper one) */
  sign_bit = _mm_and_ps(sign_bit, *(v4sf*)_ps_sign_mask);
  
  /* compute x mod PIO4 */
  y = _mm_mul_ps(*(v4sf*)_ps_cephes_FOPI, x);
  /* integer part of x/(PI/4) */
  j = _mm_cvttps_epi32(y);
  y = _mm_cvtepi32_ps(j);
  
  /* map zeros and singularities to origin */
  emm0 = _mm_and_si128(j, *(v4si*)_pi32_1);
  emm0 = _mm_cmpeq_epi32(emm0, *(v4si*)_pi32_1);
  j = _mm_add_epi32(j, _mm_and_si128(emm0, *(v4si*)_pi32_1));
  xmm0 = _mm_cvtepi32_ps(emm0);
  y = _mm_add_ps(y, _mm_and_ps(xmm0, *(v4sf*)_ps_1));
  
  /* z = ((x - y * DP1) - y * DP2) - y * DP3; */
  xmm0 = _mm_add_ps(x, _mm_mul_ps(y, *(v4sf*)_ps_minus_cephes_DP1));
  xmm1 = _mm_add_ps(xmm0, _mm_mul_ps(y, *(v4sf*)_ps_minus_cephes_DP2));
  z = _mm_add_ps(xmm1, _mm_mul_ps(y, *(v4sf*)_ps_minus_cephes_DP3));
  
  zz = _mm_mul_ps(z, z);
  
  /* 1.7e-8 relative error in [-pi/4, +pi/4] */ 
  xmm0 = _mm_mul_ps(*(v4sf*)_ps_tanf_p0, zz);
  xmm1 = _mm_add_ps(xmm0, *(v4sf*)_ps_tanf_p1);
  xmm0 = _mm_mul_ps(xmm1, zz);
  xmm1 = _mm_add_ps(xmm0, *(v4sf*)_ps_tanf_p2);
  xmm0 = _mm_mul_ps(xmm1, zz);
  xmm1 = _mm_add_ps(xmm0, *(v4sf*)_ps_tanf_p3);
  xmm0 = _mm_mul_ps(xmm1, zz);
  xmm1 = _mm_add_ps(xmm0, *(v4sf*)_ps_tanf_p4);
  xmm0 = _mm_mul_ps(xmm1, zz);
  xmm1 = _mm_add_ps(xmm0, *(v4sf*)_ps_tanf_p5);
  xmm0 = _mm_mul_ps(xmm1, zz);
  xmm1 = _mm_mul_ps(xmm0, z);
  y = _mm_add_ps(xmm1, z);
  
  /* calculate the negative reciprocal of y */
  xmm1 = rcp_ps(y);
  xmm1 = _mm_xor_ps(xmm1, *(v4sf*)_ps_sign_mask);
  
  emm0 = _mm_and_si128(j, *(v4si*)_pi32_2);
  emm0 = _mm_cmpeq_epi32(emm0, *(v4si*)_pi32_2);
  xmm0 = _mm_castsi128_ps(emm0);
  y = _mm_or_ps(_mm_andnot_ps(xmm0, y), _mm_and_ps(xmm0, xmm1));
  
  /* do the sign */
  y = _mm_xor_ps(sign_bit, y);
  
  return y;
}
#endif /* _CEPHES_TAN_H_ */
