/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec3.h 
 * Handles 3d vectors
 *
 */

#ifndef _GMATH_VEC3_H_
#define _GMATH_VEC3_H_

#include "constants.h"
#include "types.h"

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec3
#define VEC_SIZE 3
#define VEC_PREFIX(X) vec3##X

static inline m128_float vec3_dot_m128(const vec3 v1, const vec3 v2);
	
#include "internal/vec.h"

static inline vec3 vec3_cross(const vec3 v1, const vec3 v2)
{
	vec3 v;
#ifndef __SSE__
	v[X] = v1[Y]*v2[Z] - v1[Z]*v2[Y];
	v[Y] = v1[Z]*v2[X] - v1[X]*v2[Z];
	v[Z] = v1[X]*v2[Y] - v1[Y]*v2[X];
#else
	__m128 tmp0, tmp1, tmp2, tmp3;
	tmp0 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3,0,2,1));
	tmp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3,1,0,2));
	tmp2 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3,1,0,2));
	tmp3 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3,0,2,1));
	v = _mm_sub_ps(_mm_mul_ps(tmp0, tmp1), _mm_mul_ps(tmp2, tmp3));
#endif
	return v;
}

static inline float vec3_dot(const vec3 v1, const vec3 v2)
{
#ifndef __SSE__
	float dot;
	for (int i = 0; i < 3; i++)
		dot += v1[i] * v2[i];
	return dot;
#else
	vec4 v = vec3_dot_m128(v1, v2);
	return m128_to_float(v);
#endif
}

static inline m128_float vec3_dot_m128(const vec3 v1, const vec3 v2)
{
#ifndef __SSE__
	return vec3_dot(v1, v2);
#else
	__m128 xyzw = _mm_mul_ps(v1, v2);
	__m128 yxwz = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2,3,0,1));
	__m128 xy = _mm_add_ss(xyzw, yxwz);
	__m128 zzww = _mm_unpackhi_ps(xyzw, xyzw);
	return _mm_cvtss_f32(_mm_add_ss(xy, zzww));
#endif
}

#endif /* _GMATH_VEC3_H_ */
