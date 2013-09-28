/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec.h 
 * Handles 3,4 sized vectors if VEC_TYPE, VEC_PREFIX and VEC_SIZE is defined
 *
 */

static inline VEC_TYPE VEC_PREFIX(_add)(const VEC_TYPE v1, const VEC_TYPE v2)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] + v2[i];
#else
	v = _mm_add_ps(v1, v2);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_sub)(const VEC_TYPE v1, const VEC_TYPE v2)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] - v2[i];
#else
	v = _mm_sub_ps(v1, v2);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_neg)(const VEC_TYPE v1)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = -v1[i];
#else
	__m128 m = _mm_castsi128_ps(_mm_set_epi32
		(0x80000000, 0x80000000, 0x80000000, 0x80000000));
	v = _mm_xor_ps(m, v1);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_mul)(const VEC_TYPE v1, const VEC_TYPE v2)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v = v1[i] * v2[i];
#else
	v = _mm_mul_ps(v1, v2);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_max)(const VEC_TYPE v1, const VEC_TYPE v2)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] > v2[i] ? v1[i] : v2[i];
#else
	v = _mm_max_ps(v1, v2);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_min)(const VEC_TYPE v1, const VEC_TYPE v2)
{
	VEC_TYPE v;
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] < v2[i] ? v1[i] : v2[i];
#else
	v = _mm_min_ps(v1, v2);
#endif
	return v;
}

static inline VEC_TYPE VEC_PREFIX(_scale_m128)(const VEC_TYPE v1, const m128_float f);

static inline VEC_TYPE VEC_PREFIX(_scale)(const VEC_TYPE v1, const float f)
{
#ifndef __SSE__
	VEC_TYPE v;
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] * f;
	return v;
#else
	return VEC_PREFIX(_scale_m128)(v1, _mm_load1_ps(&f));
#endif
}

static inline VEC_TYPE VEC_PREFIX(_scale_m128)(const VEC_TYPE v1, const m128_float f)
{
	VEC_TYPE v;
#ifndef __SSE__
	return VEC_PREFIX(_scale)(v1, f);
#else
	v = _mm_mul_ps(v1, f);
	return v;
#endif
}

static inline m128_float VEC_PREFIX(_length_m128)(const VEC_TYPE v1);
	
static inline float VEC_PREFIX(_length)(const VEC_TYPE v1)
{
#ifndef __SSE__
	return sqrtf(VEC_DOT(v1, v1));
#else
	vec4 v = VEC_PREFIX(_length_m128)(v1);
	return m128_to_float(v);
#endif
}

static inline m128_float VEC_PREFIX(_length_m128)(const VEC_TYPE v1)
{
#ifndef __SSE__
	return VEC_PREFIX(_length)(v1);
#else
	return _mm_sqrt_ps(VEC_PREFIX(_dot_m128)(v1, v1));
#endif
}

static inline VEC_TYPE VEC_PREFIX(_normalize)(const VEC_TYPE v1)
{
#ifndef __SSE__
	return VEC_PREFIX(_scale)(v1, 1.0f / VEC_PREFIX(_length)(v1));
#else
	VEC_TYPE v;
	v = _mm_mul_ps(v1, _mm_rcp_ps(VEC_PREFIX(_length_m128)(v1)));
	return v;
#endif
}

static inline VEC_TYPE VEC_PREFIX(_lerp_m128)(const VEC_TYPE v1, const VEC_TYPE v2,
                                  const m128_float f);

static inline VEC_TYPE VEC_PREFIX(_lerp)(const VEC_TYPE v1, const VEC_TYPE v2, const float f)
{
#ifndef __SSE__
	VEC_TYPE v;
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = v1[i] + (v2[i] - v1[i]) * f;
	return v;
#else
	return VEC_PREFIX(_lerp_m128)(v1, v2, float_to_m128(f));
#endif
}

static inline VEC_TYPE VEC_PREFIX(_lerp_m128)(const VEC_TYPE v1, const VEC_TYPE v2, const m128_float f)
{
#ifndef __SSE__
	return VEC_PREFIX(_lerp)(v1, v2, f);
#else
	VEC_TYPE v;
	__m128 tmp0 = _mm_sub_ps(v2, v1);
	__m128 tmp1 = _mm_mul_ps(tmp1, f);
	v = _mm_add_ps(v1, tmp1);
	return v;
#endif
}
