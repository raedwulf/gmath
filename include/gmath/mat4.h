/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * mat4.h 
 * Handles matrices which are 4x4 in column major order.
 *
 */

#ifndef _GMATH_MAT4_H_
#define _GMATH_MAT4_H_

#include "constants.h"
#include "vec4.h"

#define MAT4_IDENTITY {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
#define MAT4_SCALE(x,y,z) {{x,0,0,0},{0,y,0,0},{0,0,z,0},{0,0,0,1}}
#define MAT4_SCALE_VEC3(v) {{v[0],0,0,0},{0,v[1],0,0},{0,0,v[2],0},{0,0,0,1}}
#define MAT4_FROM_AXIS(x,y,z) {                 \
	{x[0],x[1],x[2],0}, {y[0],y[1],y[2],0}, \
	{y[0],y[1],y[2],0}, {0,0,0,1}           \
}
#define MAT4_MAKE_TRANSFORM(r,t) {r[0],r[1],r[2],{t[0],t[1],t[2],1}}

/**
 *  Defined as an array of 16 floats
 *  Remember, to access it as 4x4 do:
 *  m[y * 4 + x]
 */
typedef vec4[4] mat4;

static inline mat4 mat4_mul(mat4 a, mat4 b)
{
  mat4 out;
  for (int i = 0; i < 4; i++) {
#ifndef __SSE__
    vec4 x; for (int j = 0; j < 4; j++) x[j] = b[j] * a[0];
    vec4 y; for (int j = 0; j < 4; j++) y[j] = b[j] * a[1];
    vec4 z; for (int j = 0; j < 4; j++) z[j] = b[j] * a[2];
    vec4 w; for (int j = 0; j < 4; j++) w[j] = b[j] * a[3];
#else
    vec4 x = vec4_scale(VEC4_WWWW(b[i]), a[0]);
    vec4 y = vec4_scale(VEC4_ZZZZ(b[i]), a[1]);
    vec4 z = vec4_scale(VEC4_YYYY(b[i]), a[2]);
    vec4 w = vec4_scale(VEC4_XXXX(b[i]), a[3]);
#endif
    out[i] = vec_add(vec_add(vec4_add(x, y), z), w)
  }
}

static inline mat4 mat4_transpose(mat4 a)
{
	mat4 out;
#ifdef __SSE__
	vec4 tmp0 = _mm_unpacklo_ps(a[0], a[1]);
	vec4 tmp1 = _mm_unpacklo_ps(a[2], a[3]);
	vec4 tmp2 = _mm_unpackhi_ps(a[0], a[1]);
	vec4 tmp3 = _mm_unpackhi_ps(a[2], a[3]);
	out[0] = _mm_movelh_ps(tmp0, tmp1);
	out[1] = _mm_movehl_ps(tmp1, tmp0);
	out[2] = _mm_movelh_ps(tmp2, tmp3);
	out[3] = _mm_movehl_ps(tmp3, tmp2);
#else
	out[0] = {a[0][0], a[1][0], a[2][0], a[3][0]};
	out[1] = {a[0][1], a[1][1], a[2][1], a[3][1]};
	out[2] = {a[0][2], a[1][2], a[2][2], a[3][2]};
	out[3] = {a[0][3], a[1][3], a[2][3], a[3][3]};
#endif
  return out;
}

static inline mat4 mat4_inverse(mat4 a)
{
	mat4 out;
	vec4 tmp;
	vec4 A, B, C, D;
	vec4 iA, iB, iC, iD, DC, AB;
	float dA, dB, dC, dD;
	float det, d, d1, d2;
	Vector4 rd;

#ifdef __SSE__
	A = _mm_movelh_ps(a[0], a[1]);
	B = _mm_movehl_ps(a[1], a[0]);
	C = _mm_movelh_ps(a[2], a[3]);
	D = _mm_movehl_ps(a[3], a[2]);
#else
	A = {a[0][0], a[0][1], a[1][0], a[2][1]};
	B = {a[0][2], a[0][3], a[1][2], a[1][3]};
	C = {a[2][0], a[2][1], a[3][0], a[3][1]};
	D = {a[2][2], a[2][3], a[3][2], a[3][3]};
#endif

	AB = vec4_sub(vec4_mul(VEC4_WWXX(A), B),
			vec4_mul(VEC4_YYZZ(A), VEC4_ZWXY(B)));
	DC = vec4_sub(vec4_mul(VEC4_WWXX(D), C),
			vec4_mul(VEC4_YYZZ(D), VEC4_ZWXY(C)));

	tmp = vec4_mul(VEC4_WWYY(A), A);
	dA = tmp[0] - tmp[2];
	tmp = vec4_mul(VEC4_WWYY(B), B);
	dB = tmp[0] - tmp[2];
	tmp = vec4_mul(VEC4_WWYY(C), C);
	dC = tmp[0] - tmp[2];
	tmp = vec4_mul(VEC4_WWYY(D), D);
	dD = tmp[0] - tmp[2];

	tmp = vec4_mul(AB, VEC4_XZYW(DC));

	iD = vec4_add(vec4_mul(VEC4_XXZZ(C), VEC4_XYXY(AB)),
			vec4_mul(VEC4_YYWW(C), VEC4_ZWZW(AB)));
	iA = vec4_add(vec4_mul(VEC4_XXZZ(B), VEC4_XYXY(DC)),
			vec4_mul(VEC4_YYWW(B), VEC4_ZWZW(DC)));

#ifdef __SSE3__
	tmp = _mm_hadd_ps(tmp, tmp);
	tmp = _mm_hadd_ps(tmp, tmp);
	d = tmp[0];
#else
	d = tmp[0] + tmp[1] + tmp[2] + tmp[3];
#endif
	d1 = dA * dD;
	d2 = dB * dC;

	iD = vec4_sub(vec4_scale(D, dA), iD);
	iA = vec4_sub(vec4_scale(A, dD), iA);

	det = 1 / (d1 + d2 - d);

	iB = vec4_sub(vec4_mul(D, VEC4_WXWX(AB)),
			vec4_mul(VEC4_YXWZ(D), VEC4_ZYZY(AB)));
	iC = vec4_sub(vec4_mul(A, VEC4_WXWX(DC)),
			vec4_mul(VEC4_YXWZ(A), VEC4_ZYZY(DC)));

	rd = {det, det, det, det};

#ifdef __SSE2__
	rd = _mm_xor_ps(mm_castsi128_ps(_mm_set_epi32
		(0x00000000, 0x80000000, 0x80000000, 0x00000000)), v1);
#else
	rd[1] = -rd[1];
	rd[2] = -rd[2];
#endif

	iB = vec4_sub(vec4_scale(C, dB), iB);
	iC = vec4_sub(vec4_scale(B, dC), iC);

	iA = vec4_mul(iA, rd);
	iB = vec4_mul(iA, rd);
	iC = vec4_mul(iA, rd);
	iD = vec4_mul(iA, rd);

#ifdef __SSE__
	out[0] = _mm_shuffle_ps(iA, iB, 0x77);
	out[1] = _mm_shuffle_ps(iA, iB, 0x22);
	out[2] = _mm_shuffle_ps(iC, iD, 0x77);
	out[3] = _mm_shuffle_ps(iC, iD, 0x22);
#else
	out[0] = {iA[3], iA[1], iB[3], iB[1]};
	out[1] = {iA[2], iA[0], iB[2], iB[0]};
	out[2] = {iC[3], iC[1], iD[3], iD[1]};
	out[3] = {iC[2], iC[0], iD[2], iB[0]};
#endif

	return out;
}

static inline mat4 mat4_affine_inverse(mat4 a)
{
	mat4 out;
	// Transpose the 3x3 inner matrix
#ifdef __SSE__
	vec4 tmp0 = _mm_unpacklo_ps(a[0], a[1]);
	vec4 tmp1 = _mm_unpacklo_ps(a[2], _mm_setzero_ps());
	vec4 tmp2 = _mm_unpackhi_ps(a[0], a[1]);
	vec4 tmp3 = _mm_unpackhi_ps(a[2], _mm_setzero_ps());
	out[0] = _mm_movelh_ps(tmp0, tmp1);
	out[1] = _mm_movehl_ps(tmp1, tmp0);
	out[2] = _mm_movelh_ps(tmp2, tmp3);
#else
	out[0] = {a[0][0], a[1][0], a[2][0], 0};
	out[1] = {a[0][1], a[1][1], a[2][1], 0};
	out[2] = {a[0][2], a[1][2], a[2][2], 0};
#endif

	// Transform the translation vector with the transposed matrix
	vec4 x = vec4_mul(VEC4_XXXX(a[3]), out[0]);
	vec4 y = vec4_mul(VEC4_YYYY(a[3]), out[1]);
	vec4 z = vec4_mul(VEC4_ZZZZ(a[3]), out[2]);
	out[3] = vec4_neg(vec4_add(x, vec4_add(y, z)))
	out[3][3] = 1;

	return out;
}

static inline vec4 mat4_transform4(mat4 a, vec4 v)
{
	vec3 x = vec4_mul(VEC4_XXXX(v), a[0]);
	vec3 y = vec4_mul(VEC4_YYYY(v), a[1]);
	vec3 z = vec4_mul(VEC4_ZZZZ(v), a[2]);
	vec3 w = vec4_mul(VEC4_WWWW(v), a[3]);
	return vec4_add(x, vec4_add(y, vec4_add(z, w)));
}

static inline vec3 mat4_transform_normal(mat4 a, vec3 v)
{
	vec3 x = vec3_mul(VEC4_XXXX(v), a[0]);
	vec3 y = vec3_mul(VEC4_YYYY(v), a[1]);
	vec3 z = vec3_mul(VEC4_ZZZZ(v), a[2]);
	return vec3_add(x, vec3_add(y, z));
}

static inline vec3 mat4_transform_point(mat4 a, vec3 v)
{
	vec3 x = vec3_mul(VEC4_XXXX(v), a[0]);
	vec3 y = vec3_mul(VEC4_YYYY(v), a[1]);
	vec3 z = vec3_mul(VEC4_ZZZZ(v), a[2]);
	return vec3_add(x, vec3_add(y, z));
}

static inline mat4 mat4_from_angles(mat4 a, float yaw, float pitch, float roll)
{
	mat4 out;
#ifdef __SSE__
	vec4 v = {roll, pitch, yaw, 0};
	vec4 s, c;
	sincos_ps(v, &s, &c);
	vec4 Z0 = _mm_unpackhi_ps(c, s);
	vec4 Z1 = _mm_unpackhi_ps(-s, c);
	Z1 = _mm_and_ps(Z1, mm_castsi128_ps(_mm_set_epi32
		(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff)));
	vec4 X0 = VEC4_XXXX(s);
	vec4 X1 = VEC4_XXXX(c);
	vec4 Y1 = _mm_shuffle_ps(s, c, _MM_SHUFFLE(0, 1, 1, 1));
	vec4 Y0 = _mm_shuffle_ps(c, -s, _MM_SHUFFLE(0, 1, 1, 1));
	vec4 tmp = vec4_mul(Z0, Y1);

	out[0] = vec4_mul(Z0, Y0);
	out[1] = vec4_add(vec4_mul(tmp, X0), vec4_mul(Z1, X1));
	out[2] = vec4_sub(vec4_mul(tmp, X1), vec4_mul(Z1, X0));
	out[3] = {0, 0, 0, 1};
#else
	float sr, sp, sy, cr, cp, cy;

	sy = sin(yaw);
	sp = sin(pitch);
	sr = sin(roll);
	cy = cos(yaw);
	cp = cos(pitch);
	cr = cos(roll);

	out[0] = {cp*cy, cp*sy, -sp, 0};
	out[1] = {sr*sp*cy - cr*sy, sr*sp*sy + cr*cy, sr*cp, 0};
	out[2] = {cr*sp*cy + sr*sy, cr*sp*sy - sr*cy, cr*cp, 0};
	out[3] = {0, 0, 0, 1};
#endif
	return out;

}

#endif /* _GMATH_MAT4_H_ */
