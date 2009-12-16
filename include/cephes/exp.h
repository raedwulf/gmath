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

/* (C) 2009 Ralph Eastwood -  Added header guard */
#ifndef _CEPHES_EXP_H_
#define _CEPHES_EXP_H_

#include "common.h"

static inline v4sf exp_ps(v4sf x) {
  v4sf tmp = _mm_setzero_ps(), fx;
#ifdef USE_SSE2
  v4si emm0;
#else
  v2si mm0, mm1;
#endif
  v4sf one = *(v4sf*)_ps_1;

  x = _mm_min_ps(x, *(v4sf*)_ps_exp_hi);
  x = _mm_max_ps(x, *(v4sf*)_ps_exp_lo);

  /* express exp(x) as exp(g + n*log(2)) */
  fx = _mm_mul_ps(x, *(v4sf*)_ps_cephes_LOG2EF);
  fx = _mm_add_ps(fx, *(v4sf*)_ps_0p5);

  /* how to perform a floorf with SSE: just below */
#ifndef USE_SSE2
  /* step 1 : cast to int */
  tmp = _mm_movehl_ps(tmp, fx);
  mm0 = _mm_cvttps_pi32(fx);
  mm1 = _mm_cvttps_pi32(tmp);
  /* step 2 : cast back to float */
  tmp = _mm_cvtpi32x2_ps(mm0, mm1);
#else
  emm0 = _mm_cvttps_epi32(fx);
  tmp  = _mm_cvtepi32_ps(emm0);
#endif
  /* if greater, substract 1 */
  v4sf mask = _mm_cmpgt_ps(tmp, fx);    
  mask = _mm_and_ps(mask, one);
  fx = _mm_sub_ps(tmp, mask);

  tmp = _mm_mul_ps(fx, *(v4sf*)_ps_cephes_exp_C1);
  v4sf z = _mm_mul_ps(fx, *(v4sf*)_ps_cephes_exp_C2);
  x = _mm_sub_ps(x, tmp);
  x = _mm_sub_ps(x, z);

  z = _mm_mul_ps(x,x);
  
  v4sf y = *(v4sf*)_ps_cephes_exp_p0;
  y = _mm_mul_ps(y, x);
  y = _mm_add_ps(y, *(v4sf*)_ps_cephes_exp_p1);
  y = _mm_mul_ps(y, x);
  y = _mm_add_ps(y, *(v4sf*)_ps_cephes_exp_p2);
  y = _mm_mul_ps(y, x);
  y = _mm_add_ps(y, *(v4sf*)_ps_cephes_exp_p3);
  y = _mm_mul_ps(y, x);
  y = _mm_add_ps(y, *(v4sf*)_ps_cephes_exp_p4);
  y = _mm_mul_ps(y, x);
  y = _mm_add_ps(y, *(v4sf*)_ps_cephes_exp_p5);
  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, x);
  y = _mm_add_ps(y, one);

  /* build 2^n */
#ifndef USE_SSE2
  z = _mm_movehl_ps(z, fx);
  mm0 = _mm_cvttps_pi32(fx);
  mm1 = _mm_cvttps_pi32(z);
  mm0 = _mm_add_pi32(mm0, *(v2si*)_pi32_0x7f);
  mm1 = _mm_add_pi32(mm1, *(v2si*)_pi32_0x7f);
  mm0 = _mm_slli_pi32(mm0, 23); 
  mm1 = _mm_slli_pi32(mm1, 23);
  
  v4sf pow2n; 
  COPY_MM_TO_XMM(mm0, mm1, pow2n);
  _mm_empty();
#else
  emm0 = _mm_cvttps_epi32(fx);
  emm0 = _mm_add_epi32(emm0, *(v4si*)_pi32_0x7f);
  emm0 = _mm_slli_epi32(emm0, 23);
  v4sf pow2n = _mm_castsi128_ps(emm0);
#endif
  y = _mm_mul_ps(y, pow2n);
  return y;
}

#endif /* _CEPHES_EXP_H_ */
