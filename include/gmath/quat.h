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

/**
 *  Defined as an array of 16 floats
 *  Remember, to access it as 4x4 do:
 *  m[y * 4 + x]
 */
typedef float[4] quat;

static inline quat quat_mul(const quat q1, const quat q2)
{
	quat q;
        q[0] = q1[Y] * q2[Z] - q1[Z] *q2[Y] +
               q2[X] * q1[W] + q1[X] *q2[W];
        q[1] = q1[Z] * q2[X] - q1[X] *q2[Z] +
               q2[Y] * q1[W] + q1[Y] *q2[W];
        q[2] = q1[X] * q2[Y] - q1[Y] *q2[X] +
               q2[Z] * q1[W] + q1[Z] *q2[W];
        q[3] = q1[W] * q2[W] - q1[X] *q2[X] +
               q1[Y] * q2[Y] + q1[Z] *q2[Z]};
	return q;
}

static inline quat quat_from_euler(const vec3 euler)
{
        quat roll  = { sinf(euler[X] * 0.5f), 0, 0, cosf(euler[X] * 0.5f)};
        quat pitch = { 0, sinf(euler[Y] * 0.5f), 0, cosf(euler[Y] * 0.5f)};
        quat yaw   = { 0, 0, sinf(euler[Z] * 0.5f), cosf(euler[Z] * 0.5f)};

        return quat_mult(quat_mult(pitch, roll), yaw);
}

#endif /* _GMATH_QUAT_H_ */
