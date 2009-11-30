/* SIMD (SSE1+MMX or SSE2) implementation of sin, cos, exp and log

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library

   The default is to use the SSE1 version. If you define USE_SSE2 the
   the SSE2 intrinsics will be used in place of the MMX intrinsics. Do
   not expect any significant performance improvement with SSE2.
*/

/* Copyright (C) 2007 Julien Pommier, 2009 Ralph Eastwood

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

#ifndef _CEPHES_COS_H_
#define _CEPHES_COS_H_

#include "common.h"

/* almost the same as sin_ps */
v4sf cos_ps(v4sf x) { // any x
  v4sf xmm1, xmm2 = _mm_setzero_ps(), xmm3, y;
#ifdef USE_SSE2
  v4si emm0, emm2;
#else
  v2si mm0, mm1, mm2, mm3;
#endif
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  
  /* scale by 4/Pi */
  y = _mm_mul_ps(x, *(v4sf*)_ps_cephes_FOPI);
  
#ifdef USE_SSE2
  /* store the integer part of y in mm0 */
  emm2 = _mm_cvttps_epi32(y);
  /* j=(j+1) & (~1) (see the cephes sources) */
  emm2 = _mm_add_epi32(emm2, *(v4si*)_pi32_1);
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_inv1);
  y = _mm_cvtepi32_ps(emm2);

  emm2 = _mm_sub_epi32(emm2, *(v4si*)_pi32_2);
  
  /* get the swap sign flag */
  emm0 = _mm_andnot_si128(emm2, *(v4si*)_pi32_4);
  emm0 = _mm_slli_epi32(emm0, 29);
  /* get the polynom selection mask */
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_2);
  emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
  
  v4sf sign_bit = _mm_castsi128_ps(emm0);
  v4sf poly_mask = _mm_castsi128_ps(emm2);
#else
  /* store the integer part of y in mm0:mm1 */
  xmm2 = _mm_movehl_ps(xmm2, y);
  mm2 = _mm_cvttps_pi32(y);
  mm3 = _mm_cvttps_pi32(xmm2);

  /* j=(j+1) & (~1) (see the cephes sources) */
  mm2 = _mm_add_pi32(mm2, *(v2si*)_pi32_1);
  mm3 = _mm_add_pi32(mm3, *(v2si*)_pi32_1);
  mm2 = _mm_and_si64(mm2, *(v2si*)_pi32_inv1);
  mm3 = _mm_and_si64(mm3, *(v2si*)_pi32_inv1);

  y = _mm_cvtpi32x2_ps(mm2, mm3);


  mm2 = _mm_sub_pi32(mm2, *(v2si*)_pi32_2);
  mm3 = _mm_sub_pi32(mm3, *(v2si*)_pi32_2);

  /* get the swap sign flag in mm0:mm1 and the 
     polynom selection mask in mm2:mm3 */

  mm0 = _mm_andnot_si64(mm2, *(v2si*)_pi32_4);
  mm1 = _mm_andnot_si64(mm3, *(v2si*)_pi32_4);
  mm0 = _mm_slli_pi32(mm0, 29);
  mm1 = _mm_slli_pi32(mm1, 29);

  mm2 = _mm_and_si64(mm2, *(v2si*)_pi32_2);
  mm3 = _mm_and_si64(mm3, *(v2si*)_pi32_2);

  mm2 = _mm_cmpeq_pi32(mm2, _mm_setzero_si64());
  mm3 = _mm_cmpeq_pi32(mm3, _mm_setzero_si64());

  v4sf sign_bit, poly_mask;
  COPY_MM_TO_XMM(mm0, mm1, sign_bit);
  COPY_MM_TO_XMM(mm2, mm3, poly_mask);
  _mm_empty(); /* good-bye mmx */
#endif
  /* The magic pass: "Extended precision modular arithmetic" 
     x = ((x - y * DP1) - y * DP2) - y * DP3; */
  xmm1 = *(v4sf*)_ps_minus_cephes_DP1;
  xmm2 = *(v4sf*)_ps_minus_cephes_DP2;
  xmm3 = *(v4sf*)_ps_minus_cephes_DP3;
  xmm1 = _mm_mul_ps(y, xmm1);
  xmm2 = _mm_mul_ps(y, xmm2);
  xmm3 = _mm_mul_ps(y, xmm3);
  x = _mm_add_ps(x, xmm1);
  x = _mm_add_ps(x, xmm2);
  x = _mm_add_ps(x, xmm3);
  
  /* Evaluate the first polynom  (0 <= x <= Pi/4) */
  y = *(v4sf*)_ps_coscof_p0;
  v4sf z = _mm_mul_ps(x,x);

  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *(v4sf*)_ps_coscof_p1);
  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *(v4sf*)_ps_coscof_p2);
  y = _mm_mul_ps(y, z);
  y = _mm_mul_ps(y, z);
  v4sf tmp = _mm_mul_ps(z, *(v4sf*)_ps_0p5);
  y = _mm_sub_ps(y, tmp);
  y = _mm_add_ps(y, *(v4sf*)_ps_1);
  
  /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

  v4sf y2 = *(v4sf*)_ps_sincof_p0;
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *(v4sf*)_ps_sincof_p1);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *(v4sf*)_ps_sincof_p2);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_mul_ps(y2, x);
  y2 = _mm_add_ps(y2, x);

  /* select the correct result from the two polynoms */  
  xmm3 = poly_mask;
  y2 = _mm_and_ps(xmm3, y2); //, xmm3);
  y = _mm_andnot_ps(xmm3, y);
  y = _mm_add_ps(y,y2);
  /* update the sign */
  y = _mm_xor_ps(y, sign_bit);

  return y;
}

#endif /* _CEPHES_COS_H_ */
