/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec4.h 
 * Handles 3d vectors
 *
 */

#ifndef _GMATH_VEC4_H_
#define _GMATH_VEC4_H_

#include "constants.h"
#include "types.h"

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec4
#define VEC_SIZE 4
#define VEC_PREFIX(X) vec4##X

static inline m128_float vec4_dot_m128(const vec4 v1, const vec4 v2);
	
#include "internal/vec.h"

static inline float vec4_dot(const vec4 v1, const vec4 v2)
{
#ifndef __SSE__
	float dot;
	for (int i = 0; i < 4; i++)
		dot += v1[i] * v2[i];
	return dot;
#else
	vec4 v = vec4_dot_m128(v1, v2);
	return m128_to_float(v);
#endif
}

static inline m128_float vec4_dot_m128(const vec4 v1, const vec4 v2)
{
#ifndef __SSE__
	return vec4_dot(v1, v2);
#else
	__m128 v = _mm_mul_ps(v1, v2);
	__m128 tmp0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0,0,0,0));
	__m128 tmp1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1,1,1,1));
	__m128 tmp2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2,2,2,2));
	__m128 tmp3 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3,3,3,3));
	return _mm_add_ps(tmp0, _mm_add_ps(tmp1, _mm_add_ps(tmp2, tmp3)));
#endif
}
#endif /* _GMATH_VEC4_H_ */
