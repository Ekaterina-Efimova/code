#include "s21_tests.h"

START_TEST(test_parce_1) {

  Parametrs *p = get_param();

  bool err = parce_param("samples/0.obj");

  ck_assert_int_eq(err, SUCCESS);
  ck_assert_int_eq(p->count_poligons, 20000);
  ck_assert_int_eq(p->v->count_dots, 20000);
  // 5080 11395 14443
  ck_assert_int_eq(p->f[0].count_edges, 3);
  ck_assert_int_eq(p->f[0].edges[0], 5080);
  ck_assert_int_eq(p->f[0].edges[1], 11395);
  ck_assert_int_eq(p->f[0].edges[2], 14443);
  // v 0.78 0.39 0.84
  ck_assert_double_eq_tol(p->v->dots[0].x, 0.78,1e-6);
  ck_assert_double_eq_tol(p->v->dots[0].y, 0.39,1e-6);
  ck_assert_double_eq_tol(p->v->dots[0].z, 0.84,1e-6);
  ck_assert_double_eq_tol(p->v->min_max_y[1], FLT_MAX, 1e-6);
  ck_assert_double_eq_tol(p->v->min_max_y[0], DBL_MIN, 1e-6);

  free_param(p);
}
END_TEST

Suite *test_parce() {
  Suite *s = suite_create("Test parce");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_parce_1);

  suite_add_tcase(s, tc_core);
  return s;
}
