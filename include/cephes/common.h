/* SIMD (SSE1+MMX or SSE2) implementation of cephes math library

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library

   The default is to use the SSE1 version. If you define USE_SSE2 the
   the SSE2 intrinsics will be used in place of the MMX intrinsics. Do
   not expect any significant performance improvement with SSE2.
   
   This is an improved version from Julien Pommier.
*/

/* Copyright (C) 2007  Julien Pommier, Ralph Eastwood

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
#ifndef _CEPHES_COMMON_H_
#define _CEPHES_COMMON_H_

#include <xmmintrin.h>

#ifdef _MSC_VER /* visual c++ */
# define ALIGN16_BEG __declspec(align(16))
# define ALIGN16_END 
#else /* gcc or icc */
# define ALIGN16_BEG
# define ALIGN16_END __attribute__((aligned(16)))
#endif

typedef __m128 v4sf;  // vector of 4 float (sse1)

#ifdef USE_SSE2
# include <emmintrin.h>
typedef __m128i v4si; // vector of 4 int (sse2)
#else
typedef __m64 v2si;   // vector of 2 int (mmx)
#endif

/* declare some SSE constants -- why can't I figure a better way to do that? */
#define _PS_CONST(Name, Val)                                            \
  static const ALIGN16_BEG float _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PI32_CONST(Name, Val)                                            \
  static const ALIGN16_BEG int _pi32_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val)                                 \
  static const ALIGN16_BEG Type _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }

#include "constants.h"

#if defined (__MINGW32__)

/* the ugly part below: many versions of gcc used to be completely buggy with respect to some intrinsics
   The movehl_ps is fixed in mingw 3.4.5, but I found out that all the _mm_cmp* intrinsics were completely
   broken on my mingw gcc 3.4.5 ...

   Note that the bug on _mm_cmp* does occur only at -O0 optimization level
*/

inline __m128 my_movehl_ps(__m128 a, const __m128 b) {
	asm (
			"movhlps %2,%0\n\t"
			: "=x" (a)
			: "0" (a), "x"(b)
	    );
	return a;                                 }
#warning "redefined _mm_movehl_ps (see gcc bug 21179)"
#define _mm_movehl_ps my_movehl_ps

inline __m128 my_cmplt_ps(__m128 a, const __m128 b) {
	asm (
			"cmpltps %2,%0\n\t"
			: "=x" (a)
			: "0" (a), "x"(b)
	    );
	return a;               
                  }
inline __m128 my_cmpgt_ps(__m128 a, const __m128 b) {
	asm (
			"cmpnleps %2,%0\n\t"
			: "=x" (a)
			: "0" (a), "x"(b)
	    );
	return a;               
}
inline __m128 my_cmpeq_ps(__m128 a, const __m128 b) {
	asm (
			"cmpeqps %2,%0\n\t"
			: "=x" (a)
			: "0" (a), "x"(b)
	    );
	return a;               
}
#warning "redefined _mm_cmpxx_ps functions..."
#define _mm_cmplt_ps my_cmplt_ps
#define _mm_cmpgt_ps my_cmpgt_ps
#define _mm_cmpeq_ps my_cmpeq_ps
#endif

#ifndef USE_SSE2
typedef union xmm_mm_union {
  __m128 xmm;
  __m64 mm[2];
} xmm_mm_union;

#define COPY_XMM_TO_MM(xmm_, mm0_, mm1_) {          \
    xmm_mm_union u; u.xmm = xmm_;                   \
    mm0_ = u.mm[0];                                 \
    mm1_ = u.mm[1];                                 \
}

#define COPY_MM_TO_XMM(mm0_, mm1_, xmm_) {                         \
    xmm_mm_union u; u.mm[0]=mm0_; u.mm[1]=mm1_; xmm_ = u.xmm;      \
  }

#endif // USE_SSE2

#endif /* _CEPHES_COMMON_H_ */
