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
#include <gmath/vec3.h>
#include <gmath/vec4.h>

FCT_BGN()
{
	FCT_FIXTURE_SUITE_BGN("vec")
	{
		FCT_SETUP_BGN()
		{
		}
		FCT_SETUP_END();

		FCT_TEARDOWN_BGN()
		{
		}
		FCT_TEARDOWN_END();

		FCT_TEST_BGN("vec3_add")
		{
			vec3 v1 = {1.0f, 2.0f, 3.0f};
			vec3 v2 = {3.0f, 2.0f, 1.0f};
			vec3 v3 = vec3_add(v1, v2);
			fct_chk(fidx(v3, 0) == 4.0f);
			fct_chk(fidx(v3, 1) == 4.0f);
			fct_chk(fidx(v3, 2) == 4.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_sub")
		{
			vec3 v1 = {1.0f, 2.0f, 3.0f};
			vec3 v2 = {3.0f, 2.0f, 1.0f};
			vec3 v3 = vec3_sub(v1, v2);
			fct_chk(fidx(v3, 0) == -2.0f);
			fct_chk(fidx(v3, 1) == 0.0f);
			fct_chk(fidx(v3, 2) == 2.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_neg")
		{
			vec3 v1 = {2.0f, -1.0f, 3.0f};
			vec3 v2 = vec3_neg(v1);
			fct_chk(fidx(v2, 0) == -2.0f);
			fct_chk(fidx(v2, 1) == 1.0f);
			fct_chk(fidx(v2, 2) == -3.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_mul")
		{
			vec3 v1 = {2.0f, -1.0f, 3.0f};
			vec3 v2 = {2.0f, -1.0f, 3.0f};
			vec3 v3 = vec3_mul(v1, v2);
			fct_chk(fidx(v3, 0) == 4.0f);
			fct_chk(fidx(v3, 1) == 1.0f);
			fct_chk(fidx(v3, 2) == 9.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_scale")
		{
			vec3 v1 = {2.0f, 5.0f, -1.0f};
			vec3 v2 = vec3_scale(v1, 5.0f);
			fct_chk(fidx(v2, 0) = 10.0f);
			fct_chk(fidx(v2, 1) = 25.0f);
			fct_chk(fidx(v2, 2) = -5.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_scale_m128")
		{
			vec3 v1 = {2.0f, 5.0f, -1.0f};
			m128_float mf = float_to_m128_const(5.0f);
			vec3 v2 = vec3_scale_m128(v1, mf);
			fct_chk(fidx(v2, 0) = 10.0f);
			fct_chk(fidx(v2, 1) = 25.0f);
			fct_chk(fidx(v2, 2) = -5.0f);
		}
		FCT_TEST_END();

		FCT_TEST_BGN("vec3_cross")
		{
			vec3 v1 = {1.0f, 2.0f, 3.0f};
			vec3 v2 = {3.0f, 2.0f, 1.0f};
			vec3 v3 = vec3_cross(v1, v2);
			fct_chk(fidx(v3, 0) = 0.0f);
			fct_chk(fidx(v3, 1) = 0.0f);
			fct_chk(fidx(v3, 2) = 0.0f);
		}
		FCT_TEST_END();

	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
