/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * mat4.h 
 * Handles matrices which are 4x4
 *
 */

#ifndef _GMATH_MAT4_H_
#define _GMATH_MAT4_H_

#include "constants.h"

/**
 *  Defined as an array of 16 floats
 *  Remember, to access it as 4x4 do:
 *  m[y * 4 + x]
 */
typedef float[16] mat4;

#endif /* _GMATH_MAT4_H_ */
