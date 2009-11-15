/**
 * libgmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec3.h 
 * Handles 3d vectors
 *
 */

#ifndef _GMATH_TYPES_H_
#define _GMATH_TYPES_H_

#include <math.h>
#include <assert.h>

#ifdef __SSE__
#include <xmmintrin.h>
#include <emmintrin.h>
#endif

#include "constants.h"

#ifndef __SSE__
typedef float m128_float; 
static inline m128_float float_to_m128(float f)
{
	return f;
}
static inline float m128_to_float(m128_float f)
{
	return f;
}
#else
typedef __m128 m128_float;
static inline m128_float float_to_m128(float f)
{
	return _mm_load1_ps(&f);
}
static inline float m128_to_float(m128_float f)
{
	return *((float *)&f);
}
#endif

#endif /* _GMATH_TYPES_H_ */
