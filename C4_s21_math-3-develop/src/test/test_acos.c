#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_acos(0.0), acos(0.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_acos(-0.0), acos(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
  ck_assert_ldouble_nan(acos(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_ldouble_nan(s21_acos(S21_INF_POS));
  ck_assert_ldouble_nan(acos(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_ldouble_nan(s21_acos(S21_INF_NEG));
  ck_assert_ldouble_nan(cos(S21_INF_NEG));
}
END_TEST

START_TEST(positive_normal_1) {
  double val = 0.53226;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

START_TEST(positive_normal_2) {
  double val = 0.0322443;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e+21;
  ck_assert_ldouble_nan(s21_acos(val));
  ck_assert_ldouble_nan(acos(val));
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21;
  ck_assert_double_eq(s21_acos(val), acos(val));
}
END_TEST

START_TEST(negative_normal_1) {
  double val = -0.565326;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

START_TEST(negative_normal_2) {
  double val = -0.9274884;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

START_TEST(negative_big) {
  double val = -1e+21;
  ck_assert_ldouble_nan(s21_acos(val));
  ck_assert_ldouble_nan(acos(val));
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21;
  ck_assert_ldouble_eq(s21_acos(val), acos(val));
}
END_TEST

START_TEST(one_positive) {
  double val = 1;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

START_TEST(one_negative) {
  double val = -1;
  ck_assert_double_eq_tol(s21_acos(val), acos(val), 0.000001);
}
END_TEST

Suite *s21_acos_cases(void) {
  Suite *suite = suite_create("s21_acos_cases");
  TCase *tc = tcase_create("acos_tc");

  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, minus_zero);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, plus_inf);
  tcase_add_test(tc, negative_inf);
  // стандартные случаи
  tcase_add_test(tc, positive_normal_1);
  tcase_add_test(tc, positive_normal_2);
  tcase_add_test(tc, positive_big);
  tcase_add_test(tc, positive_little);

  tcase_add_test(tc, negative_normal_1);
  tcase_add_test(tc, negative_normal_2);
  tcase_add_test(tc, negative_big);
  tcase_add_test(tc, negative_little);

  tcase_add_test(tc, one_positive);
  tcase_add_test(tc, one_negative);

  suite_add_tcase(suite, tc);
  return suite;
}
