/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * sincos.h 
 * Handles 3,4 sized packed sin and cos operations
 *
 */
#ifndef _GMATH_SINCOS_H_
#define _GMATH_SINCOS_H_

#include "constants.h"
#include "types.h"

#ifndef __SSE__

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec3
#define VEC_SIZE 3
#define VEC_PREFIX(X) vec3##X

#include "internal/sincos.h"

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec4
#define VEC_SIZE 4
#define VEC_PREFIX(X) vec4##X

#include "internal/sincos.h"

#else /* __SSE__ */

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec4
#define VEC_SIZE 4
#define VEC_PREFIX(X) vec4##X

#include "internal/sincos.h"

#define vec3_sin vec4_sin
#define vec3_cos vec4_cos
#define vec3_sincos vec4_sincos

#endif

#endif /* _GMATH_SINCOS_H_ */
