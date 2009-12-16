/* SIMD (SSE1+MMX or SSE2) implementation of sin, cos, exp and log

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library

   The default is to use the SSE1 version. If you define USE_SSE2 the
   the SSE2 intrinsics will be used in place of the MMX intrinsics. Do
   not expect any significant performance improvement with SSE2.
*/

/* Copyright (C) 2007  Julien Pommier

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

/* (C) 2009 Ralph Eastwood -  Added header guard */
#ifndef _SINCOSLOGEXP_H_
#define _SINCOSLOGEXP_H_

#include "common.h"

_PS_CONST(minus_cephes_DP1, -0.78515625);
_PS_CONST(minus_cephes_DP2, -2.4187564849853515625e-4);
_PS_CONST(minus_cephes_DP3, -3.77489497744594108e-8);
_PS_CONST(sincof_p0, -1.9515295891E-4);
_PS_CONST(sincof_p1,  8.3321608736E-3);
_PS_CONST(sincof_p2, -1.6666654611E-1);
_PS_CONST(coscof_p0,  2.443315711809948E-005);
_PS_CONST(coscof_p1, -1.388731625493765E-003);
_PS_CONST(coscof_p2,  4.166664568298827E-002);
_PS_CONST(cephes_FOPI, 1.27323954473516); // 4 / M_PI

/* since sin_ps and cos_ps are almost identical, sincos_ps could replace both of them..
   it is almost as fast, and gives you a free cosine with your sine */
static inline void sincos_ps(v4sf x, v4sf *s, v4sf *c) {
  v4sf xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
#ifdef USE_SSE2
  v4si emm0, emm2, emm4;
#else
  v2si mm0, mm1, mm2, mm3, mm4, mm5;
#endif
  sign_bit_sin = x;
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  /* extract the sign bit (upper one) */
  sign_bit_sin = _mm_and_ps(sign_bit_sin, *(v4sf*)_ps_sign_mask);
  
  /* scale by 4/Pi */
  y = _mm_mul_ps(x, *(v4sf*)_ps_cephes_FOPI);
    
#ifdef USE_SSE2
  /* store the integer part of y in emm2 */
  emm2 = _mm_cvttps_epi32(y);

  /* j=(j+1) & (~1) (see the cephes sources) */
  emm2 = _mm_add_epi32(emm2, *(v4si*)_pi32_1);
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_inv1);
  y = _mm_cvtepi32_ps(emm2);

  emm4 = emm2;

  /* get the swap sign flag for the sine */
  emm0 = _mm_and_si128(emm2, *(v4si*)_pi32_4);
  emm0 = _mm_slli_epi32(emm0, 29);
  v4sf swap_sign_bit_sin = _mm_castsi128_ps(emm0);

  /* get the polynom selection mask for the sine*/
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_2);
  emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
  v4sf poly_mask = _mm_castsi128_ps(emm2);
#else
  /* store the integer part of y in mm2:mm3 */
  xmm3 = _mm_movehl_ps(xmm3, y);
  mm2 = _mm_cvttps_pi32(y);
  mm3 = _mm_cvttps_pi32(xmm3);

  /* j=(j+1) & (~1) (see the cephes sources) */
  mm2 = _mm_add_pi32(mm2, *(v2si*)_pi32_1);
  mm3 = _mm_add_pi32(mm3, *(v2si*)_pi32_1);
  mm2 = _mm_and_si64(mm2, *(v2si*)_pi32_inv1);
  mm3 = _mm_and_si64(mm3, *(v2si*)_pi32_inv1);

  y = _mm_cvtpi32x2_ps(mm2, mm3);

  mm4 = mm2;
  mm5 = mm3;

  /* get the swap sign flag for the sine */
  mm0 = _mm_and_si64(mm2, *(v2si*)_pi32_4);
  mm1 = _mm_and_si64(mm3, *(v2si*)_pi32_4);
  mm0 = _mm_slli_pi32(mm0, 29);
  mm1 = _mm_slli_pi32(mm1, 29);
  v4sf swap_sign_bit_sin;
  COPY_MM_TO_XMM(mm0, mm1, swap_sign_bit_sin);

  /* get the polynom selection mask for the sine */

  mm2 = _mm_and_si64(mm2, *(v2si*)_pi32_2);
  mm3 = _mm_and_si64(mm3, *(v2si*)_pi32_2);
  mm2 = _mm_cmpeq_pi32(mm2, _mm_setzero_si64());
  mm3 = _mm_cmpeq_pi32(mm3, _mm_setzero_si64());
  v4sf poly_mask;
  COPY_MM_TO_XMM(mm2, mm3, poly_mask);
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

#ifdef USE_SSE2
  emm4 = _mm_sub_epi32(emm4, *(v4si*)_pi32_2);
  emm4 = _mm_andnot_si128(emm4, *(v4si*)_pi32_4);
  emm4 = _mm_slli_epi32(emm4, 29);
  v4sf sign_bit_cos = _mm_castsi128_ps(emm4);
#else
  /* get the sign flag for the cosine */
  mm4 = _mm_sub_pi32(mm4, *(v2si*)_pi32_2);
  mm5 = _mm_sub_pi32(mm5, *(v2si*)_pi32_2);
  mm4 = _mm_andnot_si64(mm4, *(v2si*)_pi32_4);
  mm5 = _mm_andnot_si64(mm5, *(v2si*)_pi32_4);
  mm4 = _mm_slli_pi32(mm4, 29);
  mm5 = _mm_slli_pi32(mm5, 29);
  v4sf sign_bit_cos;
  COPY_MM_TO_XMM(mm4, mm5, sign_bit_cos);
  _mm_empty(); /* good-bye mmx */
#endif

  sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);

  
  /* Evaluate the first polynom  (0 <= x <= Pi/4) */
  v4sf z = _mm_mul_ps(x,x);
  y = *(v4sf*)_ps_coscof_p0;

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
  v4sf ysin2 = _mm_and_ps(xmm3, y2);
  v4sf ysin1 = _mm_andnot_ps(xmm3, y);
  y2 = _mm_sub_ps(y2,ysin2);
  y = _mm_sub_ps(y, ysin1);

  xmm1 = _mm_add_ps(ysin1,ysin2);
  xmm2 = _mm_add_ps(y,y2);
 
  /* update the sign */
  *s = _mm_xor_ps(xmm1, sign_bit_sin);
  *c = _mm_xor_ps(xmm2, sign_bit_cos);
}
#endif
