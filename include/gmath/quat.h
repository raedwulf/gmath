/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * quat.h 
 * Handles quaternions
 *
 */

#ifndef _GMATH_QUAT_H_
#define _GMATH_QUAT_H_

#include "constants.h"
#include "sincoslogexp.h"

static inline quat quat_mul(const quat q1, const quat q2)
{
#ifndef __SSE__
	quat q;
        q[0] = q1[1] * q2[2] - q1[2] * q2[1] +
               q1[3] * q2[0] + q1[0] * q2[3];
        q[1] = q1[2] * q2[0] - q1[0] * q2[2] +
               q1[3] * q2[1] + q1[1] * q2[3];
        q[2] = q1[0] * q2[1] - q1[1] * q2[0] +
               q1[3] * q2[2] + q1[2] * q2[3];
        q[3] = q1[3] * q2[3] - q1[0] * q2[0] +
               q1[1] * q2[1] + q1[2] * q2[2]};
	return q;
#else
	__m128 s1 = _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(3,3,3,3));
	__m128 s2 = _mm_shuffle_ps(q1, q1, _MM_SHUFFLE(2,0,1,0));
	__m128 s3 = _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(1,2,0,0));
	__m128 s4 = _mm_shuffle_ps(q1, q1, _MM_SHUFFLE(3,3,3,1));
	__m128 s5 = _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(0,1,2,1));
	__m128 s6 = _mm_shuffle_ps(q1, q1, _MM_SHUFFLE(1,2,0,2));
	__m128 s7 = _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(2,0,1,2));
	__m128 mul4 = _mm_mul_ps(s6, s7);
	__m128 mul3 = _mm_mul_ps(s4, s5);
	__m128 mul2 = _mm_mul_ps(s2, s3);
	__m128 mul1 = _mm_mul_ps(q1, s1);
	__m128 flip1 = _mm_xor_ps(mul4, _mm_castsi128_ps(
				_mm_set_epi32(0, 0, 0, 0x80000000)));
	__m128 flip2 = _mm_xor_ps(mul3, _mm_castsi128_ps(
				_mm_set_epi32(0, 0, 0, 0x80000000)));
	__m128 ret =_mm_sub_ps(mul1, mul2);
	__m128 ret2 =_mm_add_ps(flip1, flip2);
	return _mm_add_ps(ret, ret2);
#endif
}

static inline quat quat_from_euler(const vec3 euler)
{
#ifndef __SSE__
        quat roll  = { sinf(euler[0] * 0.5f), 0, 0, cosf(euler[0] * 0.5f)};
        quat pitch = { 0, sinf(euler[1] * 0.5f), 0, cosf(euler[1] * 0.5f)};
        quat yaw   = { 0, 0, sinf(euler[2] * 0.5f), cosf(euler[2] * 0.5f)};
#else
        __m128 half = { 0.5f, 0.5f, 0.5f, 0.0f };
        __m128 e = _mm_shuffle_ps(euler, euler, _MM_SHUFFLE(3,0,1,2));
        __m128 tmp0 = _mm_mul_ps(euler, half);
        __m128 tmp1 = sin_ps(tmp0);
        __m128 tmp2 = _mm_move_ss(cos_ps(tmp0), tmp1);
        __m128 roll = _mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(1,0,0,1));
        __m128 pitch = _mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(0,2,0,2));
        __m128 yaw = _mm_shuffle_ps(tmp1, _mm_unpackhi_ps(tmp1, tmp2),
		        _MM_SHUFFLE(0,0,2,3));
#endif
        return quat_mul(quat_mul(pitch, roll), yaw);
}

#endif /* _GMATH_QUAT_H_ */
