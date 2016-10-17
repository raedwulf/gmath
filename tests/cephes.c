/**
 * gmath
 * (C) 2009 Tai Chi Minh Ralph Eastwood
 * Released under the MIT license.
 *
 * vec.c
 * Tests vec.h
 *
 */

#include "fct.h"
#include <gmath/vec4.h>
#include <cephes/sin.h>
#include <cephes/cos.h>
#include <cephes/tan.h>
#include <cephes/asin.h>
#include <cephes/atan.h>

/* DBL_EPSILON has less tolerance than we aim for. */
#ifdef DBL_EPSILON
#undef DBL_EPSILON
#endif
#define DBL_EPSILON EPSILON

#define APPROX(X,Y) (X > Y - EPSILON && X < Y + EPSILON)
#define SHOW_VALUES(T,TC,V,VS) \
	printf("\nv:        %.10f %.10f %.10f %.10f", \
			fidx(V, 0), \
			fidx(V, 1), \
			fidx(V, 2), \
			fidx(V, 3)); \
	printf("\n" #T "_ps:   %.10f %.10f %.10f %.10f", \
			fidx(VS, 0), \
			fidx(VS, 1), \
			fidx(VS, 2), \
			fidx(VS, 3)); \
	printf("\n" #TC ":      %.10f %.10f %.10f %.10f\n", \
			TC(fidx(V, 0)), \
			TC(fidx(V, 1)), \
			TC(fidx(V, 2)), \
			TC(fidx(V, 3)));

#define SHOW_VALUES2(T,TC,V1,V2,VS) \
	printf("\nv1:       %.10f %.10f %.10f %.10f", \
			fidx(V1, 0), \
			fidx(V1, 1), \
			fidx(V1, 2), \
			fidx(V1, 3)); \
	printf("\nv2:       %.10f %.10f %.10f %.10f", \
			fidx(V2, 0), \
			fidx(V2, 1), \
			fidx(V2, 2), \
			fidx(V2, 3)); \
	printf("\n" #T "_ps:   %.10f %.10f %.10f %.10f", \
			fidx(VS, 0), \
			fidx(VS, 1), \
			fidx(VS, 2), \
			fidx(VS, 3)); \
	printf("\n" #TC ":      %.10f %.10f %.10f %.10f\n", \
			TC(fidx(V1, 0), fidx(V2, 0)), \
			TC(fidx(V1, 1), fidx(V2, 1)), \
			TC(fidx(V1, 2), fidx(V2, 2)), \
			TC(fidx(V1, 3), fidx(V2, 3)));

FCT_BGN()
{
	FCT_FIXTURE_SUITE_BGN("sin")
	{
		FCT_SETUP_BGN()
		{
		}
		FCT_SETUP_END();

		FCT_TEARDOWN_BGN()
		{
		}
		FCT_TEARDOWN_END();

		FCT_TEST_BGN("sin_ps normal")
		{
			vec4 v = {100.0f, -0.1f, -3.5f, -5.3f};
			vec4 vs = sin_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), sinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), sinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), sinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), sinf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = sin_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), sinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), sinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), sinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), sinf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_fast_ps normal")
		{
			vec4 v = {1.4f, -0.1f, 0.5f, -1.3f};
			vec4 vs = sin_fast_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), sinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), sinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), sinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), sinf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_fast_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = sin_fast_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), sinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), sinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), sinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), sinf(fidx(v, 3)));
		}
		FCT_TEST_END();

		FCT_TEST_BGN("cos_ps normal")
		{
			vec4 v = {100.0f, -3.15f, 0.2f, -5.3f};
			vec4 vs = cos_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), cosf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), cosf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), cosf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), cosf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = cos_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), cosf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), cosf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), cosf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), cosf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_fast_ps normal")
		{
			vec4 v = {1.4f, -0.1f, 0.5f, -1.3f};
			vec4 vs = cos_fast_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), cosf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), cosf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), cosf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), cosf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_fast_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = cos_fast_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), cosf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), cosf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), cosf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), cosf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("tan_ps normal")
		{
			vec4 v = {100.0f, -3.15f, 0.2f, -5.3f};
			vec4 vs = tan_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), tanf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), tanf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), tanf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), tanf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("tan_ps special")
		{
			vec4 v = {PI/4.0f, -PI/4.0f, 0.0f, 0.0f};
			vec4 vs = tan_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), tanf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), tanf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), tanf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), tanf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("asin_ps normal")
		{
			vec4 v = {-0.5f, 0.3f, 0.6f, -0.8f};
			vec4 vs = asin_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), asinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), asinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), asinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), asinf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("asin_ps special")
		{
			vec4 v = {-1.0f, 0.0f, 1.0f, 0.0f};
			vec4 vs = asin_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), asinf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), asinf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), asinf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), asinf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan_ps normal")
		{
			vec4 v = {-0.5f, 0.3f, 4.0f, -0.8f};
			vec4 vs = atan_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), atanf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), atanf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), atanf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), atanf(fidx(v, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan_ps special")
		{
			vec4 v = {-1.0f, 0.0f, 1.0f, 0.0f};
			vec4 vs = atan_ps(v);
			fct_chk_eq_dbl(fidx(vs, 0), atanf(fidx(v, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), atanf(fidx(v, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), atanf(fidx(v, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), atanf(fidx(v, 3)));
		}
		FCT_TEST_END();
		FCT_TEST_BGN("atan2_ps normal")
		{
			vec4 v1 = {-0.5f, 0.083251f, 0.6f, -0.8f};
			vec4 v2 = {-0.5f, -0.026564f, 0.6f, -0.8f};
			vec4 vs = atan2_ps(v1, v2);
			fct_chk_eq_dbl(fidx(vs, 0), atan2f(fidx(v1, 0), fidx(v2, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), atan2f(fidx(v1, 1), fidx(v2, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), atan2f(fidx(v1, 2), fidx(v2, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), atan2f(fidx(v1, 3), fidx(v2, 3)));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan2_ps special")
		{
			vec4 v1 = {-2.0f, 4.0f, 1.0f, 0.0f};
			vec4 v2 = {-1.0f, 0.0f, -2.0f, 4.0f};
			vec4 vs = atan2_ps(v1, v2);
			fct_chk_eq_dbl(fidx(vs, 0), atan2f(fidx(v1, 0), fidx(v2, 0)));
			fct_chk_eq_dbl(fidx(vs, 1), atan2f(fidx(v1, 1), fidx(v2, 1)));
			fct_chk_eq_dbl(fidx(vs, 2), atan2f(fidx(v1, 2), fidx(v2, 2)));
			fct_chk_eq_dbl(fidx(vs, 3), atan2f(fidx(v1, 3), fidx(v2, 3)));
		}
		FCT_TEST_END();
	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
