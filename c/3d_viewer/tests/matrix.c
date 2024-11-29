#include "s21_tests.h"

START_TEST(test_move_1) {
  Point point = {1.0, 2.0, 3.0};
  point = move(point, 3.0, 4.0, 5.0);
  Point res_point = {4.0, 6.0, 8.0};
  ck_assert_double_eq_tol(point.x, res_point.x, 1e-6);
  ck_assert_double_eq_tol(point.y, res_point.y, 1e-6);
  ck_assert_double_eq_tol(point.z, res_point.z, 1e-6);
}
END_TEST

START_TEST(test_rotate_1) {
  Point point = {1.0, 2.0, 3.0};
  point = rotate(point, 90.0, 90.0, 90.0);
  Point res_point = {3.0, -2.0, 1.0};
  ck_assert_double_eq_tol(point.x, res_point.x, 1e-6);
  ck_assert_double_eq_tol(point.y, res_point.y, 1e-6);
  ck_assert_double_eq_tol(point.z, res_point.z, 1e-6);
}
END_TEST

START_TEST(test_scale_1) {
  Point point = {1.0, 2.0, 3.0};
  point = scale(point, 200);
  Point res_point = {2.0, 4.0, 6.0};
  ck_assert_double_eq_tol(point.x, res_point.x, 1e-6);
  ck_assert_double_eq_tol(point.y, res_point.y, 1e-6);
  ck_assert_double_eq_tol(point.z, res_point.z, 1e-6);
}
END_TEST

Suite *test_matrix() {
  Suite *s = suite_create("Test matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_move_1);
  tcase_add_test(tc_core, test_rotate_1);
  tcase_add_test(tc_core, test_scale_1);

  suite_add_tcase(s, tc_core);
  return s;
}