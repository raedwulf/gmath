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
#include "sin.h"

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
 
static inline quat quat_slerp(const quat q1, const quat q2, const float t)
{
#ifndef __SSE__
	/* Spherical linear interpolation between two quaternions */
        /* Note: SLERP is not commutative */
        quat q3 = q1;

        /* Calculate cosine */
        float cos_theta = vec4_dot(q1, q2);

        /* Use the shortest path */
        if (cos_theta < 0)
        {
                cos_theta = -cos_theta;
                q3        = vec4_neg(q2);
	}

        /* Initialize with linear interpolation */
        float scale0 = 1 - t, scale1 = t;

	/* Use spherical interpolation only if the quaternions are not very
	 * close */
        if ((1.0f - cos_theta) > 0.001f)
        {
                /* SLERP */
                float theta     = acosf(cos_theta);
                float sin_theta = sinf(theta);
                scale0 = sinf((1 - t) * theta) / sin_theta;
                scale1 = sinf(t * theta) / sin_theta;
	}

        /* Calculate final quaternion */
        quat ret = vec4_add(vec4_scale(q1, scale0), vec4_scale(q3, scale1));
        return ret;
#else
        m128_float tmp = m128_to_float(t);
        return quat_slerp_m128(q1, q2, tmp);
#endif
}

static inline quat quat_slerp_m128(const quat q1, const quat q2,
		const m128_float t)
{
#ifndef __SSE__
	quat_slerp(q1, q2, t);
#else
	__m128 tmp0 = q1;
	__m128 tmp1 = {0.0f, 0.0f, 0.0f, 0.0f};
	__m128i flipi = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
	__m128 flip = _mm_castps_si128(flipi);
	m128_float cos_theta = vec4_dot(q1, q2);
	__m128 mask = _mm_cmplt_ps(cos_theta, tmp1);
	__m128 signmask = _mm_and_ps(mask, flip);
	cos_theta = _mm_or_ps(cos_theta, signmask);
	__m128 tmp2 = _mm_or_ps(q2, signmask);
	__m128 one = {1.0f, 1.0f, 1.0f, 1.0f};
	__m128 scale0 = _mm_sub_ps(one, t);
	__m128 scale1 = t;
	
	
	
#endif
}

#endif /* _GMATH_QUAT_H_ */
