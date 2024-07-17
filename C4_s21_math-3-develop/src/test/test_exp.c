#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_exp(0.0), exp(0.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_exp(-0.0), exp(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_nan(exp(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_ldouble_eq(s21_exp(S21_INF_POS), exp(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_ldouble_eq(s21_exp(S21_INF_NEG), exp(S21_INF_NEG));
}
END_TEST

START_TEST(positive_normal) {
  double val = 3.56;
  ck_assert_double_eq_tol(s21_exp(val), exp(val), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e21;
  ck_assert_ldouble_eq(s21_exp(val), exp(val));
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21;
  ck_assert_ldouble_eq(s21_exp(val), exp(val));
}
END_TEST

START_TEST(negative_normal_1) {
  double val = -3.56;
  ck_assert_double_eq_tol(s21_exp(val), exp(val), 0.000001);
}
END_TEST

START_TEST(negative_normal_2) {
  double val = -14.56;
  ck_assert_double_eq_tol(s21_exp(val), exp(val), 0.000001);
}
END_TEST

START_TEST(negative_big) {
  double val = -1e21;
  ck_assert_ldouble_eq(s21_exp(val), exp(val));
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21;
  ck_assert_ldouble_eq(s21_exp(val), exp(val));
}
END_TEST

START_TEST(one_positive) {
  double val = 1;
  ck_assert_double_eq_tol(s21_exp(val), exp(val), 0.000001);
}
END_TEST

START_TEST(one_negative) {
  double val = -1;
  ck_assert_double_eq_tol(s21_exp(val), exp(val), 0.000001);
}
END_TEST

Suite *s21_exp_cases(void) {
  Suite *suite = suite_create("s21_exp_cases");
  TCase *tc = tcase_create("exp_tc");

  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, minus_zero);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, plus_inf);
  tcase_add_test(tc, negative_inf);
  // стандартные случаи
  tcase_add_test(tc, positive_normal);
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