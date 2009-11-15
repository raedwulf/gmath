/**
 * Sol3d
 *
 * Copyright (C) 2009 Ralph Eastwood <tcmreastwood@ntlworld.com>
 * Copyright (C) 2006-2009 Nicolas Schulz
 *
 * This file is part of Sol3d source code.
 *
 * This software is distributed under the terms of the Eclipse Public License
 * v1.0.
 *
 * A copy of the license may be obtained at:
 * http://www.eclipse.org/legal/epl-v10.html
 */

/***
 ** Math Library
 *
 *  Conventions:
 *  - Coordinate system is right-handed with positive y as up axis.
 *  - All rotation angles are counter-clockwise when looking from the positive
 *    end of the rotation axis towards the origin.
 *  - An unrotated view vector points along the negative z-axis.
 */

#ifndef _MATH_H_
#define _MATH_H_

#include "sol_platform.h"
#include <math.h>
#include <endian.h>

/* Constants */
#define MaxUInt32 0xFFFFFFFF
#define MinInt32  0x80000000
#define MaxInt32  0x7FFFFFFF
#define MaxFloat  3.402823466e+38F;

#define Pi        3.141592654f;
#define TwoPi     6.283185307f;
#define PiHalf    1.570796327f;

#define EPSILON   0.000001f

/*
 * ----------------------------------------------------------------------------
 *
 * General
 * ----------------------------------------------------------------------------
 *
 */

#define DEG2RAD(f)         (f * 0.017453293f)
#define RAD2DEG(f)         (f * 57.29577951f)
#define CLAMP(f, min, max) (((f < min) ? min : ((f > max) ? max : f))
#define MAX(a, b)          (a > b ? a : b)
#define MIN(a, b)          (a < b ? a : b)
#define FSEL(t, a, b)      (t >= 0 ? a : b)
#define SQR(x)             (x * x)

/*
 * ----------------------------------------------------------------------------
 *
 * Conversion
 * ----------------------------------------------------------------------------
 *
 */

#ifdef __LITTLE_ENDIAN
 #define FTOI_R_INDEX 0
#elif defined(__BIG_ENDIAN)
 #define FTOI_R_INDEX 1
#endif

/**
 * ftoi_r
 */
static inline int ftoi_r(double val)
{
        /* Fast round (banker's round) using Sree Kotay's method */
        /* This function is much faster than a naive cast from float to int */

        val += 6755399441055744.0;             /* Magic number: 2^52 * 1.5; */
        return ((int *)&val)[FTOI_R_INDEX];    /* Needs to be [1] for
					        * big-endian */
}

/***
 ** Vector
 */

typedef struct
{
        float x;
        float y;
        float z;
} vec3f;

/**
 * vec3f_equals
 */
static inline int vec3f_equals(const vec3f v1, const vec3f v2)
{
        return v1.x > v2.x - EPSILON && v1.x < v2.x + EPSILON &&
                                               v1.y > v2.y - EPSILON &&
               v1.y < v2.y + EPSILON &&
                      v1
                              .z > v2.z - EPSILON && v1.z < v2.z + EPSILON;
}

/**
 * vec3f_notequals
 */
static inline int vec3f_notequals(const vec3f v1, const vec3f v2)
{
        return v1.x < v2.x - EPSILON || v1.x > v2.x + EPSILON &&
               v1.y < v2.y - EPSILON || v1.y > v2.y + EPSILON &&
               v1.z < v2.z - EPSILON || v1.z > v2.z + EPSILON;
}

/**
 * vec3f_neg
 */
static inline vec3f vec3f_neg(const vec3f v)
{
        return (vec3f) { -v.x, -v.y, -v.z};
}

/**
 * vec3f_add
 */
static inline vec3f vec3f_add(const vec3f v1, const vec3f v2)
{
        return (vec3f) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

/**
 * vec3f_sub
 */
static inline vec3f vec3f_sub(const vec3f v1, const vec3f v2)
{
        return (vec3f) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

/**
 * vec3f_scale
 */
static inline vec3f vec3f_scale(const vec3f v, const float f)
{
        return (vec3f) { v.x *f, v.y *f, v.z *f};
}

/**
 * vec3f_invscale
 */
static inline vec3f vec3f_invscale(const vec3f v, const float f)
{
        return vec3f_scale(v, 1 / f);
}

/**
 * vec3f_dot
 */
static inline float vec3f_dot(const vec3f v1, const vec3f v2)
{
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/**
 * vec3f_cross
 */
static inline vec3f vec3f_cross(const vec3f v1, const vec3f v2)
{
        return (vec3f) { v1.y *v2. z - v1.z *v2.y,
                                   v1.z *v2.x - v1.x *v2.z,
                                   v1.x *v2.y - v1.y *v2.x};
}

/**
 * vec3f_length
 */
static inline float vec3f_length(const vec3f v)
{
        return sqrtf(SQR(v.x) + SQR(v.y) + SQR(v.z));
}

/**
 * vec3f_normalize
 */
static inline vec3f vec3f_normalize(const vec3f v)
{
        return vec3f_scale(v, 1.0f / vec3f_length(v));
}

/**
 * vec3f_lerp
 */
static inline vec3f vec3f_lerp(const vec3f v1, const vec3f v2, const float f)
{
        return (vec3f) { v1.x + (v2.x - v1.x) * f,
                         v1.y + (v2.y - v1.y) * f,
                         v1.z + (v2.z - v1.z) * f};
}

typedef struct
{
        float x;
        float y;
        float z;
        float w;
} vec4f;

/**
 * vec4f_add
 */
static inline vec4f vec4f_add(const vec4f v1, const vec4f v2)
{
        return (vec4f) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

/**
 * vec4f_sub
 */
static inline vec4f vec4f_sub(const vec4f v1, const vec4f v2)
{
        return (vec4f) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

/**
 * vec4f_scale
 */
static inline vec4f vec4f_scale(const vec4f v, const float f)
{
        return (vec4f) { v.x *f, v.y *f, v.z *f, v.w *f};
}

/***
 ** Quaternion
 */
typedef vec4f quat;

/**
 * quat_mult
 */
static inline quat quat_mult(const quat q1, const quat q2)
{
        return (quat) { q1.y * q2.z - q1.z *q2.y +
                        q2.x * q1.w + q1.x *q2.w,
                                  q1.z *q2.x - q1.x *q2.z +
                        q2.y * q1.w + q1.y *q2.w,
                                  q1.x *q2.y - q1.y *q2.x +
                        q2.z * q1.w + q1.z *q2.w,
                                  q1.w *q2.w - q1.x *q2.x +
                        q1.y * q2.y + q1.z *q2.z};
}

/**
 * quat_from_euler
 */
static inline quat quat_from_euler(const float euler_x, const float euler_y,
                                   const float euler_z)
{
        quat roll  = { sinf(euler_x * 0.5f), 0, 0, cosf(euler_x * 0.5f)};
        quat pitch = { 0, sinf(euler_y * 0.5f), 0, cosf(euler_y * 0.5f)};
        quat yaw   = { 0, 0, sinf(euler_z * 0.5f), cosf(euler_z * 0.5f)};

        return quat_mult(quat_mult(pitch, roll), yaw);
}

/**
 * quat_slerp
 */
static inline quat quat_slerp(const quat q1, const quat q2, const float t)
{
        /* Spherical linear interpolation between two quaternions */
        /* Note: SLERP is not commutative */
        quat q3 = q1;

        /* Calculate cosine */
        float cos_theta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z +
                          q1.w * q2.w;

        /* Use the shortest path */
        if (cos_theta < 0)
        {
                cos_theta = -cos_theta;
                q3        = (quat) { -q2.x, -q2.y, -q2.z, -q2.w};
	}

        /* Initialize with linear interpolation */
        float scale0 = 1 - t, scale1 = t;

	/* Use spherical interpolation only if the quaternions are not very
	 * close */
        if ((1 - cos_theta) > 0.001f)
        {
                /* SLERP */
                float theta     = acosf(cos_theta);
                float sin_theta = sinf(theta);
                scale0 = sinf((1 - t) * theta) / sin_theta;
                scale1 = sinf(t * theta) / sin_theta;
	}

        /* Calculate final quaternion */
        return (quat)
               { q1.x *scale0 + q3.x *scale1, q1.y *scale0 + q3.y *scale1,
                       q1.z *scale0 + q3.z *scale1, q1.w *scale0 +
                 q3.w *scale1};
}

/**
 * quat_nlerp
 */
static inline quat quat_nlerp(const quat q1, const quat q2, const float t)
{
        /* Normalized linear quaternion interpolation */
	/* Note: NLERP is faster than SLERP and commutative but does not yield
	**/
        /* constant velocity */
        quat  qt;
        float cos_theta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z +
                          q1.w * q2.w;

        /* Use the shortest path and interpolate linearly */
        if (cos_theta < 0)
		qt = (quat)
		{ q1.x + (-q2.x - q1.x) * t,
		  q1.y + (-q2.y - q1.y) * t,
		  q1.z + (-q2.z - q1.z) * t,
		  q1.w + (-q2.w - q1.w) * t};
        else
		qt = (quat)
		{ q1.x + (q2.x - q1.x) * t,
		  q1.y + (q2.y - q1.y) * t,
		  q1.z + (q2.z - q1.z) * t,
		  q1.w + (q2.w - q1.w) * t}; /* Return the normalized
					      *quaternion */
        float inv_len = 1.0f / sqrtf(qt.x * qt.x + qt.y * qt.y +
                                     qt.z * qt.z + qt.w * qt.w);
        return (quat)
               { qt.x *inv_len, qt.y *inv_len, qt.z *inv_len,
                       qt.w *inv_len};
}

/**
 * quat_invert
 */
static inline quat quat_invert(const quat q)
{
        float len = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

        if (len > 0)
        {
                float inv_len = 1.0f / len;
                return (quat) { -q.x * inv_len, -q.y * inv_len,
                                -q.z * inv_len, q.w * inv_len};
	}
        else
		return (quat) { 0.0f, 0.0f, 0.0f, 0.0f};
}

/***
 ** Matrix
 */

typedef union
{
        float c[4][4];
        float x[16];
} mat4f;

/**
 * mat4f_perspective_matrix
 */
static inline mat4f mat4f_perspective_matrix(const float l,
                                             const float r,
                                             const float b,
                                             const float t,
                                             const float n,
                                             const float f)
{
        return (mat4f)
               { 2 * n / (r - 1),
                 0,
                 0,
                 0,
                 0,
                 2 * n / (t - b),
                 0,
                 0,
                 (r + 1) / (r - 1),
                 (t + b) / (t - b),
                 -(f + n) / (f - n),
                 -1,
                 0,
                 0,
                 -2 * f * n / (f - n),
                 0};
}

/**
 * mat4f_orthogonal_matrix
 */
static inline mat4f mat4f_orthogonal_matrix(const float l,
                                            const float r,
                                            const float b,
                                            const float t,
                                            const float n,
                                            const float f)
{
        return (mat4f)
               { 2 / (r - l),
                 0,
                 0,
                 0,
                 0,
                 2 / (t - b),
                 0,
                 0,
                 0,
                 0,
                 -2 / (f - n),
                 0,
                 -(r + l) / (r - l),
                 -(t + b) / (t - b),
                 -(f + n) / (f - n),
                 0};
}

/**
 * mat4f_fast_mult_43
 */
static inline mat4f mat4f_fast_mult_43(const mat4f m1, const mat4f m2)
{
        const float *m1x = m1.x;
        const float *m2x = m2.x;
        mat4f       dst;

        dst.x[0]  = m1x[0] * m2x[0] + m1x[4] * m2x[1] + m1x[8] * m2x[2];
        dst.x[1]  = m1x[1] * m2x[0] + m1x[5] * m2x[1] + m1x[9] * m2x[2];
        dst.x[2]  = m1x[2] * m2x[0] + m1x[6] * m2x[1] + m1x[10] * m2x[2];
        dst.x[3]  = 0.0f;

        dst.x[4]  = m1x[0] * m2x[4] + m1x[4] * m2x[5] + m1x[8] * m2x[6];
        dst.x[5]  = m1x[1] * m2x[4] + m1x[5] * m2x[5] + m1x[9] * m2x[6];
        dst.x[6]  = m1x[2] * m2x[4] + m1x[6] * m2x[5] + m1x[10] * m2x[6];
        dst.x[7]  = 0.0f;

        dst.x[8]  = m1x[0] * m2x[8] + m1x[4] * m2x[9] + m1x[8] * m2x[10];
        dst.x[9]  = m1x[1] * m2x[8] + m1x[5] * m2x[9] + m1x[9] * m2x[10];
        dst.x[10] = m1x[2] * m2x[8] + m1x[6] * m2x[9] + m1x[10] * m2x[10];
        dst.x[11] = 0.0f;

        dst.x[12] = m1x[0] * m2x[12] + m1x[4] * m2x[13] + m1x[8] * m2x[14] +
                    m1x[12] * m2x[15];
        dst.x[13] = m1x[1] * m2x[12] + m1x[5] * m2x[13] + m1x[9] * m2x[14] +
                    m1x[13] * m2x[15];
        dst.x[14] = m1x[2] * m2x[12] + m1x[6] * m2x[13] + m1x[10] * m2x[14] +
                    m1x[14] * m2x[15];
        dst.x[15] = 1.0f;

        return dst;
}

/*
 * ------------
 * Constructors
 * ------------
 */

#define M4_TRANS_MAT(x, y, z) \
        (mat4f) { .c = \
                  {         { 0.0f, 0.0f, 0.0f, \
                              0.0f},{ 0.0f, 0.0f, 0.0f,          0.0f}, \
                            { 0.0f, 0.0f, 0.0f, \
                              0.0f},{ x,    y,    z,             0.0f}}}

#define M4_SCALE_MAT(x, y, z) \
        (mat4f) { .c = \
                  {         { x,    0.0f, 0.0f, \
                              0.0f},{ 0.0f, y,    0.0f,       0.0f}, \
                            { 0.0f, 0.0f, z, \
                              0.0f},{ 0.0f, 0.0f, 0.0f,       0.0f}}}

#define M4_IDENTITY_MAT \
        (mat4f) { .c = { { 1.0f, 0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 0.0f}, \
                         { 0.0f, 0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f}}}

/**
 * mat4f_identity
 */
static inline mat4f mat4f_identity()
{
        return M4_IDENTITY_MAT;
}

/**
 * mat4f_from_quat
 */
static inline mat4f mat4f_from_quat(const quat q)
{
        /* Calculate coefficients */
        float x2 = q.x + q.x, y2 = q.y + q.y, z2 = q.z + q.z;
        float xx = q.x * x2, xy = q.x * y2, xz = q.x * z2;
        float yy = q.y * y2, yz = q.y * z2, zz = q.z * z2;
        float wx = q.w * x2, wy = q.w * y2, wz = q.w * z2;

        mat4f m;

        m.c[0][0] = 1 - (yy + zz);
        m.c[1][0] = xy - wz;
        m.c[2][0] = xz + wy;
        m.c[3][0] = 0;
        m.c[0][1] = xy + wz;
        m.c[1][1] = 1 - (xx + zz);
        m.c[2][1] = yz - wx;
        m.c[3][1] = 0;
        m.c[0][2] = xz - wy;
        m.c[1][2] = yz + wx;
        m.c[2][2] = 1 - (xx + yy);
        m.c[3][2] = 0;
        m.c[0][3] = 0;
        m.c[1][3] = 0;
        m.c[2][3] = 0;
        m.c[3][3] = 1;

        return m;
}

/**
 * mat4f_translation_matrix
 */
static inline mat4f mat4f_translation_matrix(const float x,
                                             const float y,
                                             const float z)
{
        return M4_TRANS_MAT(x, y, z);
}

/**
 * mat4f_scale_matrix
 */
static inline mat4f mat4f_scale_matrix(const float x,
                                       const float y,
                                       const float z)
{
        return M4_SCALE_MAT(x, y, z);
}

/* Rotation order: YXZ [* Vector] */
static inline mat4f mat4f_rotation_matrix(const float x,
                                          const float y,
                                          const float z)
{
        return mat4f_from_quat(quat_from_euler(x, y, z));
}

/**
 * mat4f_rotation_matrix2
 */
static inline mat4f mat4f_rotation_matrix2(const vec3f axis, const float angle)
{
        vec3f scaled_axis = vec3f_scale(axis, sinf(angle * 0.5f));
        quat  q           =
        { scaled_axis.x, scaled_axis.y, scaled_axis.z, cosf(angle * 0.5f)};

        return mat4f_from_quat(q);
}

/**
 * mat4f_add
 */
static inline mat4f mat4f_add(const mat4f m1, const mat4f m2)
{
        return (mat4f)
               { m1.x[0] + m2.x[0],
                 m1.x[1] + m2.x[1],
                 m1.x[2] + m2.x[2],
                 m1.x[3] + m2.x[3],
                 m1.x[4] + m2.x[4],
                 m1.x[5] + m2.x[5],
                 m1.x[6] + m2.x[6],
                 m1.x[7] + m2.x[7],
                 m1.x[8] + m2.x[8],
                 m1.x[9] + m2.x[9],
                 m1.x[10] + m2.x[10],
                 m1.x[11] + m2.x[11],
                 m1.x[12] + m2.x[12],
                 m1.x[13] + m2.x[13],
                 m1.x[14] + m2.x[14],
                 m1.x[15] + m2.x[15]};
}

/**
 * mat4f_mult
 */
static inline mat4f mat4f_mult(const mat4f m1, const mat4f m2)
{
        return (mat4f)
               { m1.x[0] * m2.x[0] + m1.x[4] * m2.x[1] +
                 m1.x[8] * m2.x[2] + m1.x[12] * m2.x[3],
                 m1.x[1] * m2.x[0] + m1.x[5] * m2.x[1] +
                 m1.x[9] * m2.x[2] + m1.x[13] * m2.x[3],
                 m1.x[2] * m2.x[0] + m1.x[6] * m2.x[1] +
                 m1.x[10] * m2.x[2] + m1.x[14] * m2.x[3],
                 m1.x[3] * m2.x[0] + m1.x[7] * m2.x[1] +
                 m1.x[11] * m2.x[2] + m1.x[15] * m2.x[3],
                 m1.x[0] * m2.x[4] + m1.x[4] * m2.x[5] +
                 m1.x[8] * m2.x[6] + m1.x[12] * m2.x[7],
                 m1.x[1] * m2.x[4] + m1.x[5] * m2.x[5] +
                 m1.x[9] * m2.x[6] + m1.x[13] * m2.x[7],
                 m1.x[2] * m2.x[4] + m1.x[6] * m2.x[5] +
                 m1.x[10] * m2.x[6] + m1.x[14] * m2.x[7],
                 m1.x[3] * m2.x[4] + m1.x[7] * m2.x[5] +
                 m1.x[11] * m2.x[6] + m1.x[15] * m2.x[7],
                 m1.x[0] * m2.x[8] + m1.x[4] * m2.x[9] +
                 m1.x[8] * m2.x[10] + m1.x[12] * m2.x[11],
                 m1.x[1] * m2.x[8] + m1.x[5] * m2.x[9] +
                 m1.x[9] * m2.x[10] + m1.x[13] * m2.x[11],
                 m1.x[2] * m2.x[8] + m1.x[6] * m2.x[9] +
                 m1.x[10] * m2.x[10] + m1.x[14] * m2.x[11],
                 m1.x[3] * m2.x[8] + m1.x[7] * m2.x[9] +
                 m1.x[11] * m2.x[10] + m1.x[15] * m2.x[11],
                 m1.x[0] * m2.x[12] + m1.x[4] * m2.x[13] +
                 m1.x[8] * m2.x[14] + m1.x[12] * m2.x[15],
                 m1.x[1] * m2.x[12] + m1.x[5] * m2.x[13] +
                 m1.x[9] * m2.x[14] + m1.x[13] * m2.x[15],
                 m1.x[2] * m2.x[12] + m1.x[6] * m2.x[13] +
                 m1.x[10] * m2.x[14] + m1.x[14] * m2.x[15],
                 m1.x[3] * m2.x[12] + m1.x[7] * m2.x[13] +
                 m1.x[11] * m2.x[14] + m1.x[15] * m2.x[15]};
}

/**
 * mat4f_multf
 */
static inline mat4f mat4f_multf(const mat4f m, const float f)
{
        return (mat4f)
               { m.x[0] * f,
                 m.x[1] * f,
                 m.x[2] * f,
                 m.x[3] * f,
                 m.x[4] * f,
                 m.x[5] * f,
                 m.x[6] * f,
                 m.x[7] * f,
                 m.x[8] * f,
                 m.x[9] * f,
                 m.x[10] * f,
                 m.x[11] * f,
                 m.x[12] * f,
                 m.x[13] * f,
                 m.x[14] * f,
                 m.x[15] * f};
}

/*
 * ----------------------------
 * Vector-Matrix multiplication
 * ----------------------------
 */
static inline mat4f mat4f_mult_vec3f(const mat4f m, const vec3f v)
{
        return (mat4f)
               { v.x *m. c[0][0] + v.y * m.c[1][0] + v.z * m.c[2][0] +
                 m.c[3][0],
                         v.x *m.c[0][1] + v.y * m.c[1][1] + v.z * m.c[2][1] +
                 m.c[3][1],
                         v.x *m.c[0][2] + v.y * m.c[1][2] + v.z * m.c[2][2] +
                 m.c[3][2]};
}

/**
 * mat4f_mult_vec4f
 */
static inline mat4f mat4f_mult_vec4f(const mat4f m, const vec4f v)
{
        return (mat4f)
               { v.x *m. c[0][0] + v.y * m.c[1][0] + v.z * m.c[2][0] + v.w *
                 m.c[3][0],
                         v.x *m.c[0][1] + v.y * m.c[1][1] + v.z * m.c[2][1] +
                 v.w * m.c[3][1],
                         v.x *m.c[0][2] + v.y * m.c[1][2] + v.z * m.c[2][2] +
                 v.w * m.c[3][2],
                         v.x *m.c[0][3] + v.y * m.c[1][3] + v.z * m.c[2][3] +
                 v.w * m.c[3][3]};
}

/**
 * mat4f_mult33_vec3f
 */
static inline mat4f mat4f_mult33_vec3f(const mat4f m, const vec3f v)
{
        return (mat4f)
               { v.x *m. c[0][0] + v.y * m.c[1][0] + v.z * m.c[2][0],
                         v.x *m.c[0][1] + v.y * m.c[1][1] + v.z * m.c[2][1],
                         v.x *m.c[0][2] + v.y * m.c[1][2] + v.z * m.c[2][2]};
}

/***
 ** Transformations
 */

static inline mat4f mat4f_translate(const mat4f m,
                                    const float x,
                                    const float y,
                                    const float z)
{
        return mat4f_mult(M4_TRANS_MAT(x, y, z), m);
}

/**
 * mat4f_scale
 */
static inline mat4f mat4f_scale(const mat4f m,
                                const float x,
                                const float y,
                                const float z)
{
        return mat4f_mult(M4_SCALE_MAT(x, y, z), m);
}

/**
 * mat4f_rotate
 */
static inline void mat4f_rotate(const mat4f m,
                                const float x,
                                const float y,
                                const float z)
{
        mat4f_mult(mat4f_rotation_matrix(x, y, z), m);
}

/*
 * ---------------
 * Other
 * ---------------
 */

static inline mat4f mat4f_transposed(const mat4f m)
{
        mat4f mr = m;

        for (int y = 0; y < 4; y++)
		for (int x = y + 1; x < 4; x++)
		{
		        float tmp = mr.c[x][y];
		        mr.c[x][y] = mr.c[y][x];
		        mr.c[y][x] = tmp;
		}
        return mr;
}

/**
 * mat4f_determinant
 */
static inline float mat4f_determinant(const mat4f m)
{
        return
                m.c[0][3] * m.c[1][2] * m.c[2][1] * m.c[3][0] -
                m.c[0][2] * m.c[1][3] * m.c[2][1] * m.c[3][0] -
                m.c[0][3] * m.c[1][1] * m.c[2][2] * m.c[3][0] +
                m.c[0][1] * m.c[1][3] * m.c[2][2] * m.c[3][0] +
                m.c[0][2] * m.c[1][1] * m.c[2][3] * m.c[3][0] -
                m.c[0][1] * m.c[1][2] * m.c[2][3] * m.c[3][0] -
                m.c[0][3] * m.c[1][2] * m.c[2][0] * m.c[3][1] +
                m.c[0][2] * m.c[1][3] * m.c[2][0] * m.c[3][1] +
                m.c[0][3] * m.c[1][0] * m.c[2][2] * m.c[3][1] -
                m.c[0][0] * m.c[1][3] * m.c[2][2] * m.c[3][1] -
                m.c[0][2] * m.c[1][0] * m.c[2][3] * m.c[3][1] +
                m.c[0][0] * m.c[1][2] * m.c[2][3] * m.c[3][1] +
                m.c[0][3] * m.c[1][1] * m.c[2][0] * m.c[3][2] -
                m.c[0][1] * m.c[1][3] * m.c[2][0] * m.c[3][2] -
                m.c[0][3] * m.c[1][0] * m.c[2][1] * m.c[3][2] +
                m.c[0][0] * m.c[1][3] * m.c[2][1] * m.c[3][2] +
                m.c[0][1] * m.c[1][0] * m.c[2][3] * m.c[3][2] -
                m.c[0][0] * m.c[1][1] * m.c[2][3] * m.c[3][2] -
                m.c[0][2] * m.c[1][1] * m.c[2][0] * m.c[3][3] +
                m.c[0][1] * m.c[1][2] * m.c[2][0] * m.c[3][3] +
                m.c[0][2] * m.c[1][0] * m.c[2][1] * m.c[3][3] -
                m.c[0][0] * m.c[1][2] * m.c[2][1] * m.c[3][3] -
                m.c[0][1] * m.c[1][0] * m.c[2][2] * m.c[3][3] +
                m.c[0][0] * m.c[1][1] * m.c[2][2] * m.c[3][3];
}

/**
 * mat4f_invert
 */
static inline mat4f mat4f_invert(const mat4f m)
{
        mat4f mr;

        float d = mat4f_determinant(m);

        if (d == 0) return m;
        d          = 1.0f / d;

        mr.c[0][0] = d * (m.c[1][2] * m.c[2][3] * m.c[3][1] -
                          m.c[1][3] * m.c[2][2] * m.c[3][1] +
                          m.c[1][3] * m.c[2][1] * m.c[3][2] -
                          m.c[1][1] * m.c[2][3] * m.c[3][2] -
                          m.c[1][2] * m.c[2][1] * m.c[3][3] +
                          m.c[1][1] * m.c[2][2] * m.c[3][3]);

        mr.c[0][1] = d * (m.c[0][3] * m.c[2][2] * m.c[3][1] -
                          m.c[0][2] * m.c[2][3] * m.c[3][1] -
                          m.c[0][3] * m.c[2][1] * m.c[3][2] +
                          m.c[0][1] * m.c[2][3] * m.c[3][2] +
                          m.c[0][2] * m.c[2][1] * m.c[3][3] -
                          m.c[0][1] * m.c[2][2] * m.c[3][3]);

        mr.c[0][2] = d * (m.c[0][2] * m.c[1][3] * m.c[3][1] -
                          m.c[0][3] * m.c[1][2] * m.c[3][1] +
                          m.c[0][3] * m.c[1][1] * m.c[3][2] -
                          m.c[0][1] * m.c[1][3] * m.c[3][2] -
                          m.c[0][2] * m.c[1][1] * m.c[3][3] +
                          m.c[0][1] * m.c[1][2] * m.c[3][3]);

        mr.c[0][3] = d * (m.c[0][3] * m.c[1][2] * m.c[2][1] -
                          m.c[0][2] * m.c[1][3] * m.c[2][1] -
                          m.c[0][3] * m.c[1][1] * m.c[2][2] +
                          m.c[0][1] * m.c[1][3] * m.c[2][2] +
                          m.c[0][2] * m.c[1][1] * m.c[2][3] -
                          m.c[0][1] * m.c[1][2] * m.c[2][3]);

        mr.c[1][0] = d * (m.c[1][3] * m.c[2][2] * m.c[3][0] -
                          m.c[1][2] * m.c[2][3] * m.c[3][0] -
                          m.c[1][3] * m.c[2][0] * m.c[3][2] +
                          m.c[1][0] * m.c[2][3] * m.c[3][2] +
                          m.c[1][2] * m.c[2][0] * m.c[3][3] -
                          m.c[1][0] * m.c[2][2] * m.c[3][3]);

        mr.c[1][1] = d * (m.c[0][2] * m.c[2][3] * m.c[3][0] -
                          m.c[0][3] * m.c[2][2] * m.c[3][0] +
                          m.c[0][3] * m.c[2][0] * m.c[3][2] -
                          m.c[0][0] * m.c[2][3] * m.c[3][2] -
                          m.c[0][2] * m.c[2][0] * m.c[3][3] +
                          m.c[0][0] * m.c[2][2] * m.c[3][3]);

        mr.c[1][2] = d * (m.c[0][3] * m.c[1][2] * m.c[3][0] -
                          m.c[0][2] * m.c[1][3] * m.c[3][0] -
                          m.c[0][3] * m.c[1][0] * m.c[3][2] +
                          m.c[0][0] * m.c[1][3] * m.c[3][2] +
                          m.c[0][2] * m.c[1][0] * m.c[3][3] -
                          m.c[0][0] * m.c[1][2] * m.c[3][3]);

        mr.c[1][3] = d * (m.c[0][2] * m.c[1][3] * m.c[2][0] -
                          m.c[0][3] * m.c[1][2] * m.c[2][0] +
                          m.c[0][3] * m.c[1][0] * m.c[2][2] -
                          m.c[0][0] * m.c[1][3] * m.c[2][2] -
                          m.c[0][2] * m.c[1][0] * m.c[2][3] +
                          m.c[0][0] * m.c[1][2] * m.c[2][3]);

        mr.c[2][0] = d * (m.c[1][1] * m.c[2][3] * m.c[3][0] -
                          m.c[1][3] * m.c[2][1] * m.c[3][0] +
                          m.c[1][3] * m.c[2][0] * m.c[3][1] -
                          m.c[1][0] * m.c[2][3] * m.c[3][1] -
                          m.c[1][1] * m.c[2][0] * m.c[3][3] +
                          m.c[1][0] * m.c[2][1] * m.c[3][3]);

        mr.c[2][1] = d * (m.c[0][3] * m.c[2][1] * m.c[3][0] -
                          m.c[0][1] * m.c[2][3] * m.c[3][0] -
                          m.c[0][3] * m.c[2][0] * m.c[3][1] +
                          m.c[0][0] * m.c[2][3] * m.c[3][1] +
                          m.c[0][1] * m.c[2][0] * m.c[3][3] -
                          m.c[0][0] * m.c[2][1] * m.c[3][3]);

        mr.c[2][2] = d * (m.c[0][1] * m.c[1][3] * m.c[3][0] -
                          m.c[0][3] * m.c[1][1] * m.c[3][0] +
                          m.c[0][3] * m.c[1][0] * m.c[3][1] -
                          m.c[0][0] * m.c[1][3] * m.c[3][1] -
                          m.c[0][1] * m.c[1][0] * m.c[3][3] +
                          m.c[0][0] * m.c[1][1] * m.c[3][3]);

        mr.c[2][3] = d * (m.c[0][3] * m.c[1][1] * m.c[2][0] -
                          m.c[0][1] * m.c[1][3] * m.c[2][0] -
                          m.c[0][3] * m.c[1][0] * m.c[2][1] +
                          m.c[0][0] * m.c[1][3] * m.c[2][1] +
                          m.c[0][1] * m.c[1][0] * m.c[2][3] -
                          m.c[0][0] * m.c[1][1] * m.c[2][3]);

        mr.c[3][0] = d * (m.c[1][2] * m.c[2][1] * m.c[3][0] -
                          m.c[1][1] * m.c[2][2] * m.c[3][0] -
                          m.c[1][2] * m.c[2][0] * m.c[3][1] +
                          m.c[1][0] * m.c[2][2] * m.c[3][1] +
                          m.c[1][1] * m.c[2][0] * m.c[3][2] -
                          m.c[1][0] * m.c[2][1] * m.c[3][2]);

        mr.c[3][1] = d * (m.c[0][1] * m.c[2][2] * m.c[3][0] -
                          m.c[0][2] * m.c[2][1] * m.c[3][0] +
                          m.c[0][2] * m.c[2][0] * m.c[3][1] -
                          m.c[0][0] * m.c[2][2] * m.c[3][1] -
                          m.c[0][1] * m.c[2][0] * m.c[3][2] +
                          m.c[0][0] * m.c[2][1] * m.c[3][2]);

        mr.c[3][2] = d * (m.c[0][2] * m.c[1][1] * m.c[3][0] -
                          m.c[0][1] * m.c[1][2] * m.c[3][0] -
                          m.c[0][2] * m.c[1][0] * m.c[3][1] +
                          m.c[0][0] * m.c[1][2] * m.c[3][1] +
                          m.c[0][1] * m.c[1][0] * m.c[3][2] -
                          m.c[0][0] * m.c[1][1] * m.c[3][2]);

        mr.c[3][3] = d * (m.c[0][1] * m.c[1][2] * m.c[2][0] -
                          m.c[0][2] * m.c[1][1] * m.c[2][0] +
                          m.c[0][2] * m.c[1][0] * m.c[2][1] -
                          m.c[0][0] * m.c[1][2] * m.c[2][1] -
                          m.c[0][1] * m.c[1][0] * m.c[2][2] +
                          m.c[0][0] * m.c[1][1] * m.c[2][2]);

        return mr;
}

/**
 * decompose
 */
static inline void decompose(const mat4f m,
                             vec3f *trans,
                             vec3f *rot,
                             vec3f *scale)
{
        /* Getting translation is trivial */
        *trans = (vec3f) { m.c[3][0], m.c[3][1], m.c[3][2]};

        /* Scale is length of columns */
        *scale = (vec3f)
        { sqrt(m.c[0][0] * m.c[0][0] +
               m.c[0][1] * m.c[0][1] +
               m.c[0][2] * m.c[0][2]),
          sqrt(m.c[1][0] * m.c[1][0] +
               m.c[1][1] * m.c[1][1] +
               m.c[1][2] * m.c[1][2]),
          sqrt(m.c[2][0] * m.c[2][0] +
               m.c[2][1] * m.c[2][1] +
               m.c[2][2] * m.c[2][2])};

        if ((scale->x == 0) || (scale->y == 0) || (scale->z == 0)) return;

	/* Detect negative scale with determinant and flip one arbitrary axis
	**/
        if (mat4f_determinant(m) < 0)
		scale->x = -scale->x;                       /* Combined
							     *rotation matrix
							     *YXZ */
        rot->x = asinf(-m.c[2][1] / scale->z);

        /* Special case: Cos[x] == 0 (when Sin[x] is +/-1) */
        float f = fabsf(m.c[2][1] / scale->z);

        if ((f > 0.999f) && (f < 1.001f))
        {
                /* Pin arbitrarily one of y or z to zero */
                /* Mathematical equivalent of gimbal lock */
                rot->y = 0;

                /* Now: Cos[x] = 0, Sin[x] = +/-1, Cos[y] = 1, Sin[y] = 0 */
                /* => m[0][0] = Cos[z] and m[1][0] = Sin[z] */
                rot->z = atan2f(-m.c[1][0] / scale->y, m.c[0][0] / scale->x);
	}
        /* Standard case */
        else
        {
                rot->y = atan2f(m.c[2][0] / scale->z, m.c[2][2] / scale->z);
                rot->z = atan2f(m.c[0][1] / scale->x, m.c[1][1] / scale->y);
	}
}

/**
 * mat4f_get_column
 */
static inline vec4f mat4f_get_column(const mat4f m, unsigned int col)
{
        return (vec4f)
               { m.x[col * 4 + 0], m.x[col * 4 + 1],
                 m.x[col * 4 + 2], m.x[col * 4 + 3]};
}

/**
 * mat4f_get_row
 */
static inline vec4f mat4f_get_row(const mat4f m, unsigned int row)
{
        return (vec4f)
               { m.x[row + 0], m.x[row + 4],
                 m.x[row + 8], m.x[row + 12]};
}

/**
 * mat4f_get_scale
 */
static inline vec3f mat4f_get_scale(const mat4f m)
{
        /* Scale is length of columns */
        return (vec3f)
               { sqrt(m.c[0][0] * m.c[0][0] +
                      m.c[0][1] * m.c[0][1] +
                      m.c[0][2] * m.c[0][2]),
                 sqrt(m.c[1][0] * m.c[1][0] +
                      m.c[1][1] * m.c[1][1] +
                      m.c[1][2] * m.c[1][2]),
                 sqrt(m.c[2][0] * m.c[2][0] +
                      m.c[2][1] * m.c[2][1] +
                      m.c[2][2] * m.c[2][2])};
}

/*
 * ----------------------------------------------------------------------------
 *
 * Plane
 * ----------------------------------------------------------------------------
 *
 */

typedef struct
{
        vec3f normal;
        float dist;
} plane;

/**
 * plane_init
 */
static inline plane plane_init(const float a,
                               const float b,
                               const float c,
                               const float d)
{
        plane p;

        p.normal = (vec3f) { a, b, c};
        float inv_len = 1.0f / vec3f_length(p.normal);
        p.normal = vec3f_scale(p.normal, inv_len);
        p.dist   = d * inv_len;
        return p;
}

/**
 * plane_init_vec3f
 */
static inline plane plane_init_vec3f(const vec3f v0,
                                     const vec3f v1,
                                     const vec3f v2)
{
        plane p;

        p.normal =
                vec3f_normalize(vec3f_cross(vec3f_sub(v1,
                                                      v0), vec3f_sub(v2, v0)));
        p.dist = -vec3f_dot(p.normal, v0);
        return p;
}

/**
 * plane_dist_to_point
 */
static inline float plane_dist_to_point(const plane p, const vec3f v)
{
        return vec3f_dot(p.normal, v) + p.dist;
}

/***
 ** Intersection
 */

static inline int ray_triangle_intersection(const vec3f ray_orig,
                                            const vec3f ray_dir,
                                            const vec3f vert0,
                                            const vec3f vert1,
                                            const vec3f vert2,
                                            vec3f *intsPoint)
{
        /* Idea: Tomas Moeller and Ben Trumbore */
        /* in Fast, Minimum Storage Ray/Triangle Intersection */

        /* Find vectors for two edges sharing vert0 */
        vec3f edge1 = vec3f_sub(vert1, vert0);
        vec3f edge2 = vec3f_sub(vert2, vert0);

	/* Begin calculating determinant - also used to calculate U parameter
	**/
        vec3f pvec = vec3f_cross(ray_dir, edge2);

        /* If determinant is near zero, ray lies in plane of triangle */
        float det = vec3f_dot(edge1, pvec);

        /* *** Culling branch *** */
	/*if( det < Math::Epsilon )return false;
	 *
	 *  // Calculate distance from vert0 to ray origin
	 *  Vec3f tvec = ray_orig - vert0;
	 *
	 *  // Calculate U parameter and test bounds
	 *  float u = tvec.dot( pvec );
	 *  if (u < 0 || u > det ) return false;
	 *
	 *  // Prepare to test V parameter
	 *  Vec3f qvec = tvec.cross( edge1 );
	 *
	 *  // Calculate V parameter and test bounds
	 *  float v = ray_dir.dot( qvec );
	 *  if (v < 0 || u + v > det ) return false;
	 *
	 *  // Calculate t, scale parameters, ray intersects triangle
	 *  float t = edge2.dot( qvec ) / det;*/

        /* *** Non-culling branch *** */
        if ((det > -EPSILON) && (det < EPSILON)) return 0;
        float inv_det = 1.0f / det;

        /* Calculate distance from vert0 to ray origin */
        vec3f tvec = vec3f_sub(ray_orig, vert0);

        /* Calculate U parameter and test bounds */
        float u = vec3f_dot(tvec, pvec) * inv_det;

        if ((u < 0.0f) || (u > 1.0f)) return 0;

        /* Prepare to test V parameter */
        vec3f qvec = vec3f_cross(tvec, edge1);

        /* Calculate V parameter and test bounds */
        float v = vec3f_dot(ray_dir, qvec) * inv_det;

        if ((v < 0.0f) || (u + v > 1.0f)) return 0;

        /* Calculate t, ray intersects triangle */
        float t = vec3f_dot(edge2, qvec) * inv_det;

        /* Calculate intersection point and test ray length and direction */
        *intsPoint = vec3f_scale(vec3f_add(ray_orig, ray_dir), t);
        vec3f vec = vec3f_sub(*intsPoint, ray_orig);

        if ((vec3f_dot(vec, ray_dir) < 0) ||
            (vec3f_length(vec) > vec3f_length(ray_dir))) return 0;

        return 1;
}

/**
 * ray_aabb_intersection
 */
static inline int ray_aabb_intersection(const vec3f ray_orig,
                                        const vec3f ray_dir,
                                        const vec3f mins,
                                        const vec3f maxs)
{
        /* SLAB based optimized ray/AABB intersection routine */
        /* Idea taken from http://ompf.org/ray/ */

        float l1   = (mins.x - ray_orig.x) / ray_dir.x;
        float l2   = (maxs.x - ray_orig.x) / ray_dir.x;
        float lmin = MIN(l1, l2);
        float lmax = MAX(l1, l2);

        l1   = (mins.y - ray_orig.y) / ray_dir.y;
        l2   = (maxs.y - ray_orig.y) / ray_dir.y;
        lmin = MAX(MIN(l1, l2), lmin);
        lmax = MIN(MAX(l1, l2), lmax);

        l1   = (mins.z - ray_orig.z) / ray_dir.z;
        l2   = (maxs.z - ray_orig.z) / ray_dir.z;
        lmin = MAX(MIN(l1, l2), lmin);
        lmax = MIN(MAX(l1, l2), lmax);

        if ((lmax >= 0.0f) && (lmax >= lmin))
        {
                /* Consider length */
                const vec3f ray_dest = vec3f_add(ray_orig, ray_dir);
                vec3f       ray_mins =
                { MIN(ray_dest.x,      ray_orig.x),    MIN(
                          ray_dest.y,
                          ray_orig.y), MIN(ray_dest.z,
                                           ray_orig.z)};
                vec3f       ray_maxs =
                { MAX(ray_dest.x,      ray_orig.x),    MAX(
                          ray_dest.y,
                          ray_orig.y), MAX(ray_dest.z,
                                           ray_orig.z)};
                return
                        (ray_mins.x < maxs.x) && (ray_maxs.x > mins.x) &&
                        (ray_mins.y < maxs.y) && (ray_maxs.y > mins.y) &&
                        (ray_mins.z < maxs.z) && (ray_maxs.z > mins.z);
	}
        else
		return 0;
}

/**
 * nearest_dist_to_aabb
 */
static inline float nearest_dist_to_aabb(const vec3f pos,
                                         const vec3f mins,
                                         const vec3f maxs)
{
        const vec3f center     = vec3f_scale(vec3f_add(mins, maxs), 0.5f);
        const vec3f extent     = vec3f_scale(vec3f_sub(maxs, mins), 0.5f);

        vec3f       nearestVec = { MAX(0,
                                       fabsf(
                                               pos.x - center.x) - extent.x),
                                   MAX(0,
                                       fabsf(
                                               pos.y - center.y) - extent.y),
                                   MAX(0,
                                       fabsf(
                                               pos.z - center.z) - extent.z)};

        return vec3f_length(nearestVec);
}

#endif /* _MATH_H_ */
