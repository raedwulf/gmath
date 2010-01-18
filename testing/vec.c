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
#define SHOW_VALUES_VEC3(T,V1,V2,VR) \
	printf("\nv1:        %.10f %.10f %.10f", \
			fidx(V1, 0), \
			fidx(V1, 1), \
			fidx(V1, 2)); \
	printf("\nv2:        %.10f %.10f %.10f", \
			fidx(V2, 0), \
			fidx(V2, 1), \
			fidx(V2, 2)); \
	printf("\nvec3_" #T ":   %.10f %.10f %.10f\n", \
			fidx(VR, 0), \
			fidx(VR, 1), \
			fidx(VR, 2))
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
			fct_chk(fidx(v3, 0) = -4.0f);
			fct_chk(fidx(v3, 1) = 8.0f);
			fct_chk(fidx(v3, 2) = -4.0f);
		}
		FCT_TEST_END();

	}
	FCT_FIXTURE_SUITE_END();
}
FCT_END();
