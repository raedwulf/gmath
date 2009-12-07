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
#include <gmath/sincos.h>

#define APPROX(X,Y) (X > Y - EPSILON && X < Y + EPSILON)
#define SHOW_VALUES(T,V,VS) \
	printf("\nv:        %.10f %.10f %.10f %.10f", \
			fidx(v, 0), \
			fidx(v, 1), \
			fidx(v, 2), \
			fidx(v, 3)); \
	printf("\nvec4_" #T ": %.10f %.10f %.10f %.10f", \
			fidx(vs, 0), \
			fidx(vs, 1), \
			fidx(vs, 2), \
			fidx(vs, 3)); \
	printf("\n" #T "f:     %.10f %.10f %.10f %.10f\n", \
			T##f(fidx(v, 0)), \
			T##f(fidx(v, 1)), \
			T##f(fidx(v, 2)), \
			T##f(fidx(v, 3)));

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

		FCT_TEST_BGN("vec4_sin normal")
		{
			vec4 v = {3.5f, -0.1f, -3.5f, -5.3f};
			vec4 vs = vec4_sin(v);
			SHOW_VALUES(sin, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("vec4_sin special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = vec4_sin(v);
			SHOW_VALUES(sin, v, vs);
			fct_chk(APPROX(fidx(vs, 0), sinf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), sinf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), sinf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), sinf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("vec4_cos normal")
		{
			vec4 v = {3.5f, -3.15f, 0.2f, -5.3f};
			vec4 vs = vec4_cos(v);
			SHOW_VALUES(cos, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
		
		FCT_TEST_BGN("vec4_cos special")
		{
			vec4 v = {-PI/2.0f, 0.0f, PI/2.0f, 0.0f};
			vec4 vs = vec4_cos(v);
			SHOW_VALUES(cos, v, vs);
			fct_chk(APPROX(fidx(vs, 0), cosf(fidx(v, 0))));
			fct_chk(APPROX(fidx(vs, 1), cosf(fidx(v, 1))));
			fct_chk(APPROX(fidx(vs, 2), cosf(fidx(v, 2))));
			fct_chk(APPROX(fidx(vs, 3), cosf(fidx(v, 3))));
		}
		FCT_TEST_END();
	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
