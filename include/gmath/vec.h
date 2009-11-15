/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec.h 
 * Handles 3d and 4d vectors
 *
 */

#ifndef _GMATH_VEC3_H_
#define _GMATH_VEC3_H_

#include "constants.h"
#include "types.h"

#ifdef __SSE__
typedef __m128 vec4;
#else
typedef float[4] vec4;
#endif

typedef vec4 vec3;

static inline vec3 vec3_add(const vec3 v1, const vec3 v2)
{
	vec3 v;
#ifndef __SSE__
	for (int i = 0; i < 2; i++)
		v.f[i] = v1.f[i] + v2.f[i];
#else
	v = _mm_add_ps(v1, v2);
#endif
	return v;
}

static inline vec3 vec3_sub(const vec3 v1, const vec3 v2)
{
	vec3 v;
#ifndef __SSE__
	for (int i = 0; i < 2; i++)
		v.f[i] = v1.f[i] - v2.f[i];
#else
	v = _mm_sub_ps(v1, v2);
#endif
	return v;
}

static inline vec3 vec3_neg(const vec3 v1)
{
	vec3 v;
#ifndef __SSE__
	for (int i = 0; i < 2; i++)
		v.f[i] = -v1.f[i];
#else
	__m128 m = _mm_castsi128_ps(_mm_set_epi32
		(0x80000000, 0x80000000, 0x80000000, 0x80000000));
	v = _mm_xor_ps(m, v1);
#endif
	return v;
}

static inline vec3 vec3_mul(const vec3 v1, const vec3 v2)
{
	vec3 v;
#ifndef __SSE__
	for (int i = 0; i < 2; i++)
		v = v1.f[i] * v2.f[i];
#else
	v = _mm_mul_ps(v1, v2);
#endif
	return v;
}

static inline vec3 vec3_scale_m128(const vec3 v1, const m128_float f);

static inline vec3 vec3_scale(const vec3 v1, const float f)
{
	vec3 v;
#ifndef __SSE__
	for (int i = 0; i < 2; i++)
		v.f[i] = v1.f[i] * f;
	return v;
#else
	return vec3_scale_m128(v, _mm_load1_ps(&f));
#endif
}

static inline vec3 vec3_scale_m128(const vec3 v1, const m128_float f)
{
	vec3 v;
#ifndef __SSE__
	return vec3_scale(v1, f);
#else
	v = _mm_mul_ps(v1, f);
	return v;
#endif
}

static inline vec3 vec3_cross(const vec3 v1, const vec3 v2)
{
	vec3 v;
#ifndef __SSE__
	v.f[X] = v1.f[Y]*v2.f[Z] - v1.f[Z]*v2.f[Y];
	v.f[Y] = v1.f[Z]*v2.f[X] - v1.f[X]*v2.f[Z];
	v.f[Z] = v1.f[X]*v2.f[Y] - v1.f[Y]*v2.f[X];
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

static inline m128_float vec3_dot_m128(const vec3 v1, const vec3 v2);
	
static inline float vec3_dot(const vec3 v1, const vec3 v2)
{
#ifndef __SSE__
	float dot;
	for (int i = 0; i < 3; i++)
		dot += v1.f[i] * v2.f[i];
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
	__m128 v = _mm_mul_ps(v1, v2);
	__m128 tmp0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0,0,0,0));
	__m128 tmp1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1,1,1,1));
	__m128 tmp2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2,2,2,2));
	return _mm_add_ps(tmp0, _mm_add_ps(tmp1, tmp2));
#endif
}

static inline m128_float vec3_length_m128(const vec3 v1);
	
static inline float vec3_length(const vec3 v1)
{
#ifndef __SSE__
	return sqrtf(vec3_dot(v1, v1));
#else
	vec4 v = vec3_length_m128(v1);
	return m128_to_float(v);
#endif
}

static inline m128_float vec3_length_m128(const vec3 v1)
{
#ifndef __SSE__
	return vec3_length(v1);
#else
	return _mm_sqrt_ps(vec3_dot_m128(v1, v1));
#endif
}

static inline vec3 vec3_normalize(const vec3 v1)
{
#ifndef __SSE__
	return vec3_scale(v1, 1.0f / vec3_length(v1));
#else
	vec3 v;
	v = _mm_mul_ps(v1, _mm_rcp_ps(vec3_length_m128(v1)));
	return v;
#endif
}

static inline vec3 vec3_lerp_m128(const vec3 v1, const vec3 v2, const m128_float f);

static inline vec3 vec3_lerp(const vec3 v1, const vec3 v2, const float f)
{
#ifndef __SSE__
	vec3 v;
	for (int i = 0; i < 3; i++)
		v.f[i] = v1.f[i] + (v2.f[i] - v1.f[i]) * f;
	return v;
#else
	return vec3_lerp_m128(v1, v2, float_to_m128(f));
#endif
}

static inline vec3 vec3_lerp_m128(const vec3 v1, const vec3 v2, const m128_float f)
{
#ifndef __SSE__
	return vec3_lerp(v1, v2, f);
#else
	vec3 v;
	__m128 tmp0 = _mm_sub_ps(v2, v1);
	__m128 tmp1 = _mm_mul_ps(tmp1, f);
	v = _mm_add_ps(v1, tmp1);
	return v;
#endif
}

#endif /* _GMATH_VEC3_H_ */
