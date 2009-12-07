/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * internal/sincos.h 
 * Handles 3,4 sized packed sin and cos operations if 
 * VEC_TYPE, VEC_PREFIX and VEC_SIZE is defined
 *
 */

static inline VEC_TYPE VEC_PREFIX(_sin)(VEC_TYPE v)
{
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = sinf(v[i]);
#else
	/* get sign bit */
	__m128 m = _mm_castsi128_ps(_mm_set1_epi32(SIGN_MASK));
	__m128 signbit = _mm_and_ps(m, v);
	v = _mm_andnot_ps(m, v);
	/* put in domain 0 to PI/2 */
	__m128 invpi = _mm_set1_ps(1/PI);
	__m128 halfpi = _mm_set1_ps(PI/2);
	__m128 vu = _mm_add_ps(v, halfpi);
#ifdef __SSE4_1__
	__m128 p = _mm_round_ps(_mm_mul_ps(vu, invpi), _MM_FROUND_TO_ZERO);
#else
	__m128 divpi = _mm_mul_ps(vu, invpi);
	__m128 p = _mm_cvtepi32_ps(_mm_cvttps_epi32(divpi));
#endif
	vu = _mm_sub_ps(vu, _mm_mul_ps(p, _mm_set1_ps(PI)));
	v = _mm_sub_ps(vu, halfpi);
	/* Flip the sign bit if we've fixed the domain */
	__m128 d = _mm_cmpneq_ps(p, _mm_setzero_ps());
	d = _mm_and_ps(d, _mm_cmpneq_ps(vu, _mm_setzero_ps()));
	d = _mm_and_ps(m, d);
	signbit = _mm_xor_ps(signbit, d);
	v = _mm_andnot_ps(m, v);
	/* Taylor's series approximation */
	__m128 p0 = _mm_set1_ps(1.66666666666666666667e-1);
	__m128 p1 = _mm_set1_ps(8.33333333333333333333e-3);
	__m128 p2 = _mm_set1_ps(1.98412698412698412698e-4);
	__m128 p3 = _mm_set1_ps(2.75573192239858906526e-6);
	__m128 v2 = _mm_mul_ps(v, v);
	__m128 v3 = _mm_mul_ps(v, v2);
	__m128 v5 = _mm_mul_ps(v3, v2);
	__m128 v7 = _mm_mul_ps(v5, v2);
	__m128 v9 = _mm_mul_ps(v7, v2);
	__m128 x = _mm_sub_ps(v, _mm_mul_ps(v3, p0));
	x = _mm_add_ps(x, _mm_mul_ps(v5, p1));
	x = _mm_sub_ps(x, _mm_mul_ps(v7, p2));
	x = _mm_add_ps(x, _mm_mul_ps(v9, p3));
	/* if > 1, round to 1 */
	__m128 m2 = _mm_cmplt_ps(x, _mm_set1_ps(1.0f));
	__m128 isone = _mm_andnot_ps(m2, _mm_set1_ps(1.0f));
	__m128 res = _mm_or_ps(isone, _mm_and_ps(m2, x));
	/* Put sign bit back on */
	res = _mm_or_ps(signbit, res);
	return res;
#endif	
}

static inline VEC_TYPE VEC_PREFIX(_cos)(VEC_TYPE v)
{
#ifndef __SSE__
	for (int i = 0; i < VEC_SIZE; i++)
		v[i] = sinf(v[i]);
#else
	/* get sign bit */
	__m128 m = _mm_castsi128_ps(_mm_set1_epi32(SIGN_MASK));
	v = _mm_andnot_ps(m, v);
	/* put in domain 0 to PI/2 */
	__m128 invpi = _mm_set1_ps(1/PI);
	__m128 halfpi = _mm_set1_ps(PI/2);
	__m128 vu = _mm_add_ps(v, halfpi);
#ifdef __SSE4_1__
	__m128 p = _mm_round_ps(_mm_mul_ps(vu, invpi), _MM_FROUND_TO_ZERO);
#else
	__m128 divpi = _mm_mul_ps(vu, invpi);
	__m128 p = _mm_cvtepi32_ps(_mm_cvttps_epi32(divpi));
#endif
	vu = _mm_sub_ps(vu, _mm_mul_ps(p, _mm_set1_ps(PI)));
	v = _mm_sub_ps(vu, halfpi);
	/* Flip the sign bit if we've fixed the domain */
	__m128 d = _mm_cmpneq_ps(p, _mm_setzero_ps());
	d = _mm_and_ps(m, d);
	__m128 signbit = _mm_xor_ps(_mm_and_ps(m, v), d);
	v = _mm_andnot_ps(m, v);
	/* Taylor's series approximation */
	__m128 p0 = _mm_set1_ps(5e-1);
	__m128 p1 = _mm_set1_ps(4.16666666666666666667e-2);
	__m128 p2 = _mm_set1_ps(1.38888888888888888889e-3);
	__m128 p3 = _mm_set1_ps(2.48015873015873015873e-5);
	__m128 v2 = _mm_mul_ps(v, v);
	__m128 v4 = _mm_mul_ps(v2, v2);
	__m128 v6 = _mm_mul_ps(v4, v2);
	__m128 v8 = _mm_mul_ps(v6, v2);
	__m128 x = _mm_sub_ps(_mm_set1_ps(1.0f), _mm_mul_ps(v2, p0));
	x = _mm_add_ps(x, _mm_mul_ps(v4, p1));
	x = _mm_sub_ps(x, _mm_mul_ps(v6, p2));
	x = _mm_add_ps(x, _mm_mul_ps(v8, p3));
	/* if v > PI/2, round to 0 */
	__m128 m2 = _mm_cmplt_ps(v, _mm_set1_ps(PI/2));
	__m128 res = _mm_and_ps(m2, x);
	/* Put sign bit back on */
	res = _mm_or_ps(signbit, res);
	return res;
#endif	
}
