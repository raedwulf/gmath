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
#define float_to_m128(f) f
#define float_to_m128_const(f) f
#define m128_to_float(f) f
#define fidx(f,x) f[x]
#else
typedef __m128 m128_float;
#define float_to_m128(f) (_mm_load1_ps(&f))
#define float_to_m128_const(f) (_mm_set1_ps(f))
#define m128_to_float(f) (*((float *)&f))
#define fidx(f,x) (((float *)&f)[x])
#define int_to_m128_const(f) (_mm_castsi128_ps(_mm_set1_epi32(f)))
#endif

#ifdef __SSE__
typedef __m128 vec4;
#else
typedef float[4] vec4;
#endif

typedef vec4 vec3;
typedef vec4 quat;

#endif /* _GMATH_TYPES_H_ */
