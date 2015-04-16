/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec4.h 
 * Handles 3d vectors
 *
 */

#ifndef _GMATH_VEC4_H_
#define _GMATH_VEC4_H_

#include "constants.h"
#include "types.h"

#undef VEC_TYPE
#undef VEC_SIZE
#undef VEC_PREFIX

#define VEC_TYPE vec4
#define VEC_SIZE 4
#define VEC_PREFIX(X) vec4##X

static inline m128_float vec4_dot_m128(const vec4 v1, const vec4 v2);

static inline float vec4_dot(const vec4 v1, const vec4 v2)
{
#ifndef __SSE__
	float dot;
	for (int i = 0; i < 4; i++)
		dot += v1[i] * v2[i];
	return dot;
#else
	vec4 v = vec4_dot_m128(v1, v2);
	return m128_to_float(v);
#endif
}

#include "internal/vec.h"

static inline vec4 vec4_swizzle(const vec4 v, int x, int y, int z, int w)
{
#ifndef __SSE__
	return {v[x], v[y], v[z], v[w]};
#else
	return _mm_shuffle_ps(v, v,
			_MM_SHUFFLE((3-x)&3, (3-y)&3, (3-z)&3, (3-w)&3));
#endif
}

static inline m128_float vec4_dot_m128(const vec4 v1, const vec4 v2)
{
#ifndef __SSE__
	return vec4_dot(v1, v2);
#elif __SSE4__
	return _mm_dp_ps(v1, v2, 0xff);
#else
	__m128 xyzw = _mm_mul_ps(v1, v2);
	__m128 yxwz = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(2,3,0,1));
	__m128 xy2zw2 = _mm_add_ps(xyzw, yxwz);
	__m128 zw4 = _mm_unpackhi_ps(xy2zw2, xy2zw2);
	__m128 ___r = _mm_add_ss(xy2zw2, zw4);
	__m128 rrrr = _mm_shuffle_ps(___r, ___r, _MM_SHUFFLE(3,3,3,3));
	return rrrr;
#endif
}

#define VEC4_XXXX(v) (vec4_swizzle(v,0,0,0,0))
#define VEC4_XXXY(v) (vec4_swizzle(v,0,0,0,1))
#define VEC4_XXXZ(v) (vec4_swizzle(v,0,0,0,2))
#define VEC4_XXXW(v) (vec4_swizzle(v,0,0,0,3))
#define VEC4_XXYX(v) (vec4_swizzle(v,0,0,1,0))
#define VEC4_XXYY(v) (vec4_swizzle(v,0,0,1,1))
#define VEC4_XXYZ(v) (vec4_swizzle(v,0,0,1,2))
#define VEC4_XXYW(v) (vec4_swizzle(v,0,0,1,3))
#define VEC4_XXZX(v) (vec4_swizzle(v,0,0,2,0))
#define VEC4_XXZY(v) (vec4_swizzle(v,0,0,2,1))
#define VEC4_XXZZ(v) (vec4_swizzle(v,0,0,2,2))
#define VEC4_XXZW(v) (vec4_swizzle(v,0,0,2,3))
#define VEC4_XXWX(v) (vec4_swizzle(v,0,0,3,0))
#define VEC4_XXWY(v) (vec4_swizzle(v,0,0,3,1))
#define VEC4_XXWZ(v) (vec4_swizzle(v,0,0,3,2))
#define VEC4_XXWW(v) (vec4_swizzle(v,0,0,3,3))
#define VEC4_XYXX(v) (vec4_swizzle(v,0,1,0,0))
#define VEC4_XYXY(v) (vec4_swizzle(v,0,1,0,1))
#define VEC4_XYXZ(v) (vec4_swizzle(v,0,1,0,2))
#define VEC4_XYXW(v) (vec4_swizzle(v,0,1,0,3))
#define VEC4_XYYX(v) (vec4_swizzle(v,0,1,1,0))
#define VEC4_XYYY(v) (vec4_swizzle(v,0,1,1,1))
#define VEC4_XYYZ(v) (vec4_swizzle(v,0,1,1,2))
#define VEC4_XYYW(v) (vec4_swizzle(v,0,1,1,3))
#define VEC4_XYZX(v) (vec4_swizzle(v,0,1,2,0))
#define VEC4_XYZY(v) (vec4_swizzle(v,0,1,2,1))
#define VEC4_XYZZ(v) (vec4_swizzle(v,0,1,2,2))
#define VEC4_XYZW(v) (vec4_swizzle(v,0,1,2,3))
#define VEC4_XYWX(v) (vec4_swizzle(v,0,1,3,0))
#define VEC4_XYWY(v) (vec4_swizzle(v,0,1,3,1))
#define VEC4_XYWZ(v) (vec4_swizzle(v,0,1,3,2))
#define VEC4_XYWW(v) (vec4_swizzle(v,0,1,3,3))
#define VEC4_XZXX(v) (vec4_swizzle(v,0,2,0,0))
#define VEC4_XZXY(v) (vec4_swizzle(v,0,2,0,1))
#define VEC4_XZXZ(v) (vec4_swizzle(v,0,2,0,2))
#define VEC4_XZXW(v) (vec4_swizzle(v,0,2,0,3))
#define VEC4_XZYX(v) (vec4_swizzle(v,0,2,1,0))
#define VEC4_XZYY(v) (vec4_swizzle(v,0,2,1,1))
#define VEC4_XZYZ(v) (vec4_swizzle(v,0,2,1,2))
#define VEC4_XZYW(v) (vec4_swizzle(v,0,2,1,3))
#define VEC4_XZZX(v) (vec4_swizzle(v,0,2,2,0))
#define VEC4_XZZY(v) (vec4_swizzle(v,0,2,2,1))
#define VEC4_XZZZ(v) (vec4_swizzle(v,0,2,2,2))
#define VEC4_XZZW(v) (vec4_swizzle(v,0,2,2,3))
#define VEC4_XZWX(v) (vec4_swizzle(v,0,2,3,0))
#define VEC4_XZWY(v) (vec4_swizzle(v,0,2,3,1))
#define VEC4_XZWZ(v) (vec4_swizzle(v,0,2,3,2))
#define VEC4_XZWW(v) (vec4_swizzle(v,0,2,3,3))
#define VEC4_XWXX(v) (vec4_swizzle(v,0,3,0,0))
#define VEC4_XWXY(v) (vec4_swizzle(v,0,3,0,1))
#define VEC4_XWXZ(v) (vec4_swizzle(v,0,3,0,2))
#define VEC4_XWXW(v) (vec4_swizzle(v,0,3,0,3))
#define VEC4_XWYX(v) (vec4_swizzle(v,0,3,1,0))
#define VEC4_XWYY(v) (vec4_swizzle(v,0,3,1,1))
#define VEC4_XWYZ(v) (vec4_swizzle(v,0,3,1,2))
#define VEC4_XWYW(v) (vec4_swizzle(v,0,3,1,3))
#define VEC4_XWZX(v) (vec4_swizzle(v,0,3,2,0))
#define VEC4_XWZY(v) (vec4_swizzle(v,0,3,2,1))
#define VEC4_XWZZ(v) (vec4_swizzle(v,0,3,2,2))
#define VEC4_XWZW(v) (vec4_swizzle(v,0,3,2,3))
#define VEC4_XWWX(v) (vec4_swizzle(v,0,3,3,0))
#define VEC4_XWWY(v) (vec4_swizzle(v,0,3,3,1))
#define VEC4_XWWZ(v) (vec4_swizzle(v,0,3,3,2))
#define VEC4_XWWW(v) (vec4_swizzle(v,0,3,3,3))
#define VEC4_YXXX(v) (vec4_swizzle(v,1,0,0,0))
#define VEC4_YXXY(v) (vec4_swizzle(v,1,0,0,1))
#define VEC4_YXXZ(v) (vec4_swizzle(v,1,0,0,2))
#define VEC4_YXXW(v) (vec4_swizzle(v,1,0,0,3))
#define VEC4_YXYX(v) (vec4_swizzle(v,1,0,1,0))
#define VEC4_YXYY(v) (vec4_swizzle(v,1,0,1,1))
#define VEC4_YXYZ(v) (vec4_swizzle(v,1,0,1,2))
#define VEC4_YXYW(v) (vec4_swizzle(v,1,0,1,3))
#define VEC4_YXZX(v) (vec4_swizzle(v,1,0,2,0))
#define VEC4_YXZY(v) (vec4_swizzle(v,1,0,2,1))
#define VEC4_YXZZ(v) (vec4_swizzle(v,1,0,2,2))
#define VEC4_YXZW(v) (vec4_swizzle(v,1,0,2,3))
#define VEC4_YXWX(v) (vec4_swizzle(v,1,0,3,0))
#define VEC4_YXWY(v) (vec4_swizzle(v,1,0,3,1))
#define VEC4_YXWZ(v) (vec4_swizzle(v,1,0,3,2))
#define VEC4_YXWW(v) (vec4_swizzle(v,1,0,3,3))
#define VEC4_YYXX(v) (vec4_swizzle(v,1,1,0,0))
#define VEC4_YYXY(v) (vec4_swizzle(v,1,1,0,1))
#define VEC4_YYXZ(v) (vec4_swizzle(v,1,1,0,2))
#define VEC4_YYXW(v) (vec4_swizzle(v,1,1,0,3))
#define VEC4_YYYX(v) (vec4_swizzle(v,1,1,1,0))
#define VEC4_YYYY(v) (vec4_swizzle(v,1,1,1,1))
#define VEC4_YYYZ(v) (vec4_swizzle(v,1,1,1,2))
#define VEC4_YYYW(v) (vec4_swizzle(v,1,1,1,3))
#define VEC4_YYZX(v) (vec4_swizzle(v,1,1,2,0))
#define VEC4_YYZY(v) (vec4_swizzle(v,1,1,2,1))
#define VEC4_YYZZ(v) (vec4_swizzle(v,1,1,2,2))
#define VEC4_YYZW(v) (vec4_swizzle(v,1,1,2,3))
#define VEC4_YYWX(v) (vec4_swizzle(v,1,1,3,0))
#define VEC4_YYWY(v) (vec4_swizzle(v,1,1,3,1))
#define VEC4_YYWZ(v) (vec4_swizzle(v,1,1,3,2))
#define VEC4_YYWW(v) (vec4_swizzle(v,1,1,3,3))
#define VEC4_YZXX(v) (vec4_swizzle(v,1,2,0,0))
#define VEC4_YZXY(v) (vec4_swizzle(v,1,2,0,1))
#define VEC4_YZXZ(v) (vec4_swizzle(v,1,2,0,2))
#define VEC4_YZXW(v) (vec4_swizzle(v,1,2,0,3))
#define VEC4_YZYX(v) (vec4_swizzle(v,1,2,1,0))
#define VEC4_YZYY(v) (vec4_swizzle(v,1,2,1,1))
#define VEC4_YZYZ(v) (vec4_swizzle(v,1,2,1,2))
#define VEC4_YZYW(v) (vec4_swizzle(v,1,2,1,3))
#define VEC4_YZZX(v) (vec4_swizzle(v,1,2,2,0))
#define VEC4_YZZY(v) (vec4_swizzle(v,1,2,2,1))
#define VEC4_YZZZ(v) (vec4_swizzle(v,1,2,2,2))
#define VEC4_YZZW(v) (vec4_swizzle(v,1,2,2,3))
#define VEC4_YZWX(v) (vec4_swizzle(v,1,2,3,0))
#define VEC4_YZWY(v) (vec4_swizzle(v,1,2,3,1))
#define VEC4_YZWZ(v) (vec4_swizzle(v,1,2,3,2))
#define VEC4_YZWW(v) (vec4_swizzle(v,1,2,3,3))
#define VEC4_YWXX(v) (vec4_swizzle(v,1,3,0,0))
#define VEC4_YWXY(v) (vec4_swizzle(v,1,3,0,1))
#define VEC4_YWXZ(v) (vec4_swizzle(v,1,3,0,2))
#define VEC4_YWXW(v) (vec4_swizzle(v,1,3,0,3))
#define VEC4_YWYX(v) (vec4_swizzle(v,1,3,1,0))
#define VEC4_YWYY(v) (vec4_swizzle(v,1,3,1,1))
#define VEC4_YWYZ(v) (vec4_swizzle(v,1,3,1,2))
#define VEC4_YWYW(v) (vec4_swizzle(v,1,3,1,3))
#define VEC4_YWZX(v) (vec4_swizzle(v,1,3,2,0))
#define VEC4_YWZY(v) (vec4_swizzle(v,1,3,2,1))
#define VEC4_YWZZ(v) (vec4_swizzle(v,1,3,2,2))
#define VEC4_YWZW(v) (vec4_swizzle(v,1,3,2,3))
#define VEC4_YWWX(v) (vec4_swizzle(v,1,3,3,0))
#define VEC4_YWWY(v) (vec4_swizzle(v,1,3,3,1))
#define VEC4_YWWZ(v) (vec4_swizzle(v,1,3,3,2))
#define VEC4_YWWW(v) (vec4_swizzle(v,1,3,3,3))
#define VEC4_ZXXX(v) (vec4_swizzle(v,2,0,0,0))
#define VEC4_ZXXY(v) (vec4_swizzle(v,2,0,0,1))
#define VEC4_ZXXZ(v) (vec4_swizzle(v,2,0,0,2))
#define VEC4_ZXXW(v) (vec4_swizzle(v,2,0,0,3))
#define VEC4_ZXYX(v) (vec4_swizzle(v,2,0,1,0))
#define VEC4_ZXYY(v) (vec4_swizzle(v,2,0,1,1))
#define VEC4_ZXYZ(v) (vec4_swizzle(v,2,0,1,2))
#define VEC4_ZXYW(v) (vec4_swizzle(v,2,0,1,3))
#define VEC4_ZXZX(v) (vec4_swizzle(v,2,0,2,0))
#define VEC4_ZXZY(v) (vec4_swizzle(v,2,0,2,1))
#define VEC4_ZXZZ(v) (vec4_swizzle(v,2,0,2,2))
#define VEC4_ZXZW(v) (vec4_swizzle(v,2,0,2,3))
#define VEC4_ZXWX(v) (vec4_swizzle(v,2,0,3,0))
#define VEC4_ZXWY(v) (vec4_swizzle(v,2,0,3,1))
#define VEC4_ZXWZ(v) (vec4_swizzle(v,2,0,3,2))
#define VEC4_ZXWW(v) (vec4_swizzle(v,2,0,3,3))
#define VEC4_ZYXX(v) (vec4_swizzle(v,2,1,0,0))
#define VEC4_ZYXY(v) (vec4_swizzle(v,2,1,0,1))
#define VEC4_ZYXZ(v) (vec4_swizzle(v,2,1,0,2))
#define VEC4_ZYXW(v) (vec4_swizzle(v,2,1,0,3))
#define VEC4_ZYYX(v) (vec4_swizzle(v,2,1,1,0))
#define VEC4_ZYYY(v) (vec4_swizzle(v,2,1,1,1))
#define VEC4_ZYYZ(v) (vec4_swizzle(v,2,1,1,2))
#define VEC4_ZYYW(v) (vec4_swizzle(v,2,1,1,3))
#define VEC4_ZYZX(v) (vec4_swizzle(v,2,1,2,0))
#define VEC4_ZYZY(v) (vec4_swizzle(v,2,1,2,1))
#define VEC4_ZYZZ(v) (vec4_swizzle(v,2,1,2,2))
#define VEC4_ZYZW(v) (vec4_swizzle(v,2,1,2,3))
#define VEC4_ZYWX(v) (vec4_swizzle(v,2,1,3,0))
#define VEC4_ZYWY(v) (vec4_swizzle(v,2,1,3,1))
#define VEC4_ZYWZ(v) (vec4_swizzle(v,2,1,3,2))
#define VEC4_ZYWW(v) (vec4_swizzle(v,2,1,3,3))
#define VEC4_ZZXX(v) (vec4_swizzle(v,2,2,0,0))
#define VEC4_ZZXY(v) (vec4_swizzle(v,2,2,0,1))
#define VEC4_ZZXZ(v) (vec4_swizzle(v,2,2,0,2))
#define VEC4_ZZXW(v) (vec4_swizzle(v,2,2,0,3))
#define VEC4_ZZYX(v) (vec4_swizzle(v,2,2,1,0))
#define VEC4_ZZYY(v) (vec4_swizzle(v,2,2,1,1))
#define VEC4_ZZYZ(v) (vec4_swizzle(v,2,2,1,2))
#define VEC4_ZZYW(v) (vec4_swizzle(v,2,2,1,3))
#define VEC4_ZZZX(v) (vec4_swizzle(v,2,2,2,0))
#define VEC4_ZZZY(v) (vec4_swizzle(v,2,2,2,1))
#define VEC4_ZZZZ(v) (vec4_swizzle(v,2,2,2,2))
#define VEC4_ZZZW(v) (vec4_swizzle(v,2,2,2,3))
#define VEC4_ZZWX(v) (vec4_swizzle(v,2,2,3,0))
#define VEC4_ZZWY(v) (vec4_swizzle(v,2,2,3,1))
#define VEC4_ZZWZ(v) (vec4_swizzle(v,2,2,3,2))
#define VEC4_ZZWW(v) (vec4_swizzle(v,2,2,3,3))
#define VEC4_ZWXX(v) (vec4_swizzle(v,2,3,0,0))
#define VEC4_ZWXY(v) (vec4_swizzle(v,2,3,0,1))
#define VEC4_ZWXZ(v) (vec4_swizzle(v,2,3,0,2))
#define VEC4_ZWXW(v) (vec4_swizzle(v,2,3,0,3))
#define VEC4_ZWYX(v) (vec4_swizzle(v,2,3,1,0))
#define VEC4_ZWYY(v) (vec4_swizzle(v,2,3,1,1))
#define VEC4_ZWYZ(v) (vec4_swizzle(v,2,3,1,2))
#define VEC4_ZWYW(v) (vec4_swizzle(v,2,3,1,3))
#define VEC4_ZWZX(v) (vec4_swizzle(v,2,3,2,0))
#define VEC4_ZWZY(v) (vec4_swizzle(v,2,3,2,1))
#define VEC4_ZWZZ(v) (vec4_swizzle(v,2,3,2,2))
#define VEC4_ZWZW(v) (vec4_swizzle(v,2,3,2,3))
#define VEC4_ZWWX(v) (vec4_swizzle(v,2,3,3,0))
#define VEC4_ZWWY(v) (vec4_swizzle(v,2,3,3,1))
#define VEC4_ZWWZ(v) (vec4_swizzle(v,2,3,3,2))
#define VEC4_ZWWW(v) (vec4_swizzle(v,2,3,3,3))
#define VEC4_WXXX(v) (vec4_swizzle(v,3,0,0,0))
#define VEC4_WXXY(v) (vec4_swizzle(v,3,0,0,1))
#define VEC4_WXXZ(v) (vec4_swizzle(v,3,0,0,2))
#define VEC4_WXXW(v) (vec4_swizzle(v,3,0,0,3))
#define VEC4_WXYX(v) (vec4_swizzle(v,3,0,1,0))
#define VEC4_WXYY(v) (vec4_swizzle(v,3,0,1,1))
#define VEC4_WXYZ(v) (vec4_swizzle(v,3,0,1,2))
#define VEC4_WXYW(v) (vec4_swizzle(v,3,0,1,3))
#define VEC4_WXZX(v) (vec4_swizzle(v,3,0,2,0))
#define VEC4_WXZY(v) (vec4_swizzle(v,3,0,2,1))
#define VEC4_WXZZ(v) (vec4_swizzle(v,3,0,2,2))
#define VEC4_WXZW(v) (vec4_swizzle(v,3,0,2,3))
#define VEC4_WXWX(v) (vec4_swizzle(v,3,0,3,0))
#define VEC4_WXWY(v) (vec4_swizzle(v,3,0,3,1))
#define VEC4_WXWZ(v) (vec4_swizzle(v,3,0,3,2))
#define VEC4_WXWW(v) (vec4_swizzle(v,3,0,3,3))
#define VEC4_WYXX(v) (vec4_swizzle(v,3,1,0,0))
#define VEC4_WYXY(v) (vec4_swizzle(v,3,1,0,1))
#define VEC4_WYXZ(v) (vec4_swizzle(v,3,1,0,2))
#define VEC4_WYXW(v) (vec4_swizzle(v,3,1,0,3))
#define VEC4_WYYX(v) (vec4_swizzle(v,3,1,1,0))
#define VEC4_WYYY(v) (vec4_swizzle(v,3,1,1,1))
#define VEC4_WYYZ(v) (vec4_swizzle(v,3,1,1,2))
#define VEC4_WYYW(v) (vec4_swizzle(v,3,1,1,3))
#define VEC4_WYZX(v) (vec4_swizzle(v,3,1,2,0))
#define VEC4_WYZY(v) (vec4_swizzle(v,3,1,2,1))
#define VEC4_WYZZ(v) (vec4_swizzle(v,3,1,2,2))
#define VEC4_WYZW(v) (vec4_swizzle(v,3,1,2,3))
#define VEC4_WYWX(v) (vec4_swizzle(v,3,1,3,0))
#define VEC4_WYWY(v) (vec4_swizzle(v,3,1,3,1))
#define VEC4_WYWZ(v) (vec4_swizzle(v,3,1,3,2))
#define VEC4_WYWW(v) (vec4_swizzle(v,3,1,3,3))
#define VEC4_WZXX(v) (vec4_swizzle(v,3,2,0,0))
#define VEC4_WZXY(v) (vec4_swizzle(v,3,2,0,1))
#define VEC4_WZXZ(v) (vec4_swizzle(v,3,2,0,2))
#define VEC4_WZXW(v) (vec4_swizzle(v,3,2,0,3))
#define VEC4_WZYX(v) (vec4_swizzle(v,3,2,1,0))
#define VEC4_WZYY(v) (vec4_swizzle(v,3,2,1,1))
#define VEC4_WZYZ(v) (vec4_swizzle(v,3,2,1,2))
#define VEC4_WZYW(v) (vec4_swizzle(v,3,2,1,3))
#define VEC4_WZZX(v) (vec4_swizzle(v,3,2,2,0))
#define VEC4_WZZY(v) (vec4_swizzle(v,3,2,2,1))
#define VEC4_WZZZ(v) (vec4_swizzle(v,3,2,2,2))
#define VEC4_WZZW(v) (vec4_swizzle(v,3,2,2,3))
#define VEC4_WZWX(v) (vec4_swizzle(v,3,2,3,0))
#define VEC4_WZWY(v) (vec4_swizzle(v,3,2,3,1))
#define VEC4_WZWZ(v) (vec4_swizzle(v,3,2,3,2))
#define VEC4_WZWW(v) (vec4_swizzle(v,3,2,3,3))
#define VEC4_WWXX(v) (vec4_swizzle(v,3,3,0,0))
#define VEC4_WWXY(v) (vec4_swizzle(v,3,3,0,1))
#define VEC4_WWXZ(v) (vec4_swizzle(v,3,3,0,2))
#define VEC4_WWXW(v) (vec4_swizzle(v,3,3,0,3))
#define VEC4_WWYX(v) (vec4_swizzle(v,3,3,1,0))
#define VEC4_WWYY(v) (vec4_swizzle(v,3,3,1,1))
#define VEC4_WWYZ(v) (vec4_swizzle(v,3,3,1,2))
#define VEC4_WWYW(v) (vec4_swizzle(v,3,3,1,3))
#define VEC4_WWZX(v) (vec4_swizzle(v,3,3,2,0))
#define VEC4_WWZY(v) (vec4_swizzle(v,3,3,2,1))
#define VEC4_WWZZ(v) (vec4_swizzle(v,3,3,2,2))
#define VEC4_WWZW(v) (vec4_swizzle(v,3,3,2,3))
#define VEC4_WWWX(v) (vec4_swizzle(v,3,3,3,0))
#define VEC4_WWWY(v) (vec4_swizzle(v,3,3,3,1))
#define VEC4_WWWZ(v) (vec4_swizzle(v,3,3,3,2))
#define VEC4_WWWW(v) (vec4_swizzle(v,3,3,3,3))

#endif /* _GMATH_VEC4_H_ */
