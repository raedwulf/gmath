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

#define APPROX(X,Y) (X > Y - EPSILON && X < Y + EPSILON)
#define SHOW_VALUES(T,TC,V,VS) \
	printf("\nv:        %.10f %.10f %.10f %.10f", \
			fidx(v, 0), \
			fidx(v, 1), \
			fidx(v, 2), \
			fidx(v, 3)); \
	printf("\n" #T "_ps:   %.10f %.10f %.10f %.10f", \
			fidx(vs, 0), \
			fidx(vs, 1), \
			fidx(vs, 2), \
			fidx(vs, 3)); \
	printf("\n" #TC ":      %.10f %.10f %.10f %.10f\n", \
			TC(fidx(v, 0)), \
			TC(fidx(v, 1)), \
			TC(fidx(v, 2)), \
			TC(fidx(v, 3)));

#define SHOW_VALUES2(T,TC,V1,V2,VS) \
	printf("\nv1:       %.10f %.10f %.10f %.10f", \
			fidx(v1, 0), \
			fidx(v1, 1), \
			fidx(v1, 2), \
			fidx(v1, 3)); \
	printf("\nv2:       %.10f %.10f %.10f %.10f", \
			fidx(v2, 0), \
			fidx(v2, 1), \
			fidx(v2, 2), \
			fidx(v2, 3)); \
	printf("\n" #T "_ps:   %.10f %.10f %.10f %.10f", \
			fidx(vs, 0), \
			fidx(vs, 1), \
			fidx(vs, 2), \
			fidx(vs, 3)); \
	printf("\n" #TC ":      %.10f %.10f %.10f %.10f\n", \
			TC(fidx(v1, 0), fidx(v2, 0)), \
			TC(fidx(v1, 1), fidx(v2, 1)), \
			TC(fidx(v1, 2), fidx(v2, 2)), \
			TC(fidx(v1, 3), fidx(v2, 3)));

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
			SHOW_VALUES(sin, sinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = sin_ps(v);
			SHOW_VALUES(sin, sinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_fast_ps normal")
		{
			vec4 v = {1.4f, -0.1f, 0.5f, -1.3f};
			vec4 vs = sin_fast_ps(v);
			SHOW_VALUES(sin_fast, sinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("sin_fast_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = sin_fast_ps(v);
			SHOW_VALUES(sin_fast, sinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();

		FCT_TEST_BGN("cos_ps normal")
		{
			vec4 v = {100.0f, -3.15f, 0.2f, -5.3f};
			vec4 vs = cos_ps(v);
			SHOW_VALUES(cos, cosf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = cos_ps(v);
			SHOW_VALUES(cos, cosf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_fast_ps normal")
		{
			vec4 v = {1.4f, -0.1f, 0.5f, -1.3f};
			vec4 vs = cos_fast_ps(v);
			SHOW_VALUES(cos_fast, cosf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("cos_fast_ps special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = cos_fast_ps(v);
			SHOW_VALUES(cos_fast, cosf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("tan_ps normal")
		{
			vec4 v = {100.0f, -3.15f, 0.2f, -5.3f};
			vec4 vs = tan_ps(v);
			SHOW_VALUES(tan, tanf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), tanf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), tanf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), tanf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), tanf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("tan_ps special")
		{
			vec4 v = {PI/4.0f, -PI/4.0f, 0.0f, 0.0f};
			vec4 vs = tan_ps(v);
			SHOW_VALUES(tan, tanf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), tanf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), tanf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), tanf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), tanf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("asin_ps normal")
		{
			vec4 v = {-0.5f, 0.3f, 0.6f, -0.8f};
			vec4 vs = asin_ps(v);
			SHOW_VALUES(asin, asinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), asinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), asinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), asinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), asinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("asin_ps special")
		{
			vec4 v = {-1.0f, 0.0f, 1.0f, 0.0f};
			vec4 vs = asin_ps(v);
			SHOW_VALUES(asin, asinf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), asinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), asinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), asinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), asinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan_ps normal")
		{
			vec4 v = {-0.5f, 0.3f, 0.6f, -0.8f};
			vec4 vs = atan_ps(v);
			SHOW_VALUES(atan, atanf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), atanf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), atanf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), atanf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), atanf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan_ps special")
		{
			vec4 v = {-1.0f, 0.0f, 1.0f, 0.0f};
			vec4 vs = atan_ps(v);
			SHOW_VALUES(atan, atanf, v, vs);
			fct_chk(APPROX(fidx(vs, 0), atanf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), atanf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), atanf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), atanf(fidx(v, 3))));
		}
		FCT_TEST_END();
		FCT_TEST_BGN("atan2_ps normal")
		{
			vec4 v1 = {-0.5f, 0.3f, 0.6f, -0.8f};
			vec4 v2 = {-0.5f, 0.3f, 0.6f, -0.8f};
			vec4 vs = atan2_ps(v1, v2);
			SHOW_VALUES2(atan2, atan2f, v1, v2, vs);
			fct_chk(APPROX(fidx(vs, 0), atan2f(fidx(v1, 0), fidx(v2, 0))));
			fct_chk(APPROX(fidx(vs, 1), atan2f(fidx(v1, 1), fidx(v2, 1))));
			fct_chk(APPROX(fidx(vs, 2), atan2f(fidx(v1, 2), fidx(v2, 2))));
			fct_chk(APPROX(fidx(vs, 3), atan2f(fidx(v1, 3), fidx(v2, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("atan2_ps special")
		{
			vec4 v1 = {-2.0f, 4.0f, 1.0f, 0.0f};
			vec4 v2 = {-1.0f, 0.0f, 2.0f, 4.0f};
			vec4 vs = atan2_ps(v1, v2);
			SHOW_VALUES2(atan2, atan2f, v1, v2, vs);
			fct_chk(APPROX(fidx(vs, 0), atan2f(fidx(v1, 0), fidx(v2, 0))));
			fct_chk(APPROX(fidx(vs, 1), atan2f(fidx(v1, 1), fidx(v2, 1))));
			fct_chk(APPROX(fidx(vs, 2), atan2f(fidx(v1, 2), fidx(v2, 2))));
			fct_chk(APPROX(fidx(vs, 3), atan2f(fidx(v1, 3), fidx(v2, 3))));
		}
		FCT_TEST_END();
	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
