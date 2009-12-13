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
#include <cephes/asin.h>

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
	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
