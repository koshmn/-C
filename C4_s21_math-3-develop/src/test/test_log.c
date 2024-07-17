#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_log(0.0), log(0.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_log(-0.0), log(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  ck_assert_ldouble_nan(log(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_ldouble_eq(s21_log(S21_INF_POS), log(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_ldouble_nan(s21_log(S21_INF_NEG));
  ck_assert_ldouble_nan(log(S21_INF_NEG));
}
END_TEST

START_TEST(hui1) { ck_assert_ldouble_eq(s21_log(0.0 / -1.0), log(0.0 / -1.0)); }
END_TEST

START_TEST(hui2) {
  ck_assert_ldouble_nan(s21_log(0.0 / -0.0));
  ck_assert_ldouble_nan(log(0.0 / -0.0));
}
END_TEST

START_TEST(hui3) {
  ck_assert_ldouble_eq(s21_log(-1.0 / -1.0), log(-1.0 / -1.0));
}
END_TEST

START_TEST(positive_normal) {
  double val = 3.56;
  ck_assert_double_eq_tol(s21_log(val), log(val), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e6;
  ck_assert_double_eq_tol(s21_log(val), log(val), 0.000001);
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-6;
  ck_assert_double_eq_tol(s21_log(val), log(val), 0.000001);
}
END_TEST

START_TEST(negative_normal_1) {
  double val = -3.56;
  ck_assert_ldouble_nan(s21_log(val));
  ck_assert_ldouble_nan(log(val));
}
END_TEST

START_TEST(negative_normal_2) {
  double val = -14.56;
  ck_assert_ldouble_nan(s21_log(val));
  ck_assert_ldouble_nan(log(val));
}
END_TEST

START_TEST(negative_big) {
  double val = -1e6;
  ck_assert_ldouble_nan(s21_log(val));
  ck_assert_ldouble_nan(log(val));
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-6;
  ck_assert_ldouble_nan(s21_log(val));
  ck_assert_ldouble_nan(log(val));
}
END_TEST

START_TEST(one_positive) {
  double val = 1;
  ck_assert_double_eq(s21_log(val), log(val));
}
END_TEST

START_TEST(one_negative) {
  double val = -1;
  ck_assert_ldouble_nan(s21_log(val));
  ck_assert_ldouble_nan(log(val));
}
END_TEST

Suite *s21_log_cases(void) {
  Suite *suite = suite_create("s21_log_cases");
  TCase *tc = tcase_create("log_tc");

  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, minus_zero);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, plus_inf);
  tcase_add_test(tc, negative_inf);
  tcase_add_test(tc, hui1);
  tcase_add_test(tc, hui2);
  tcase_add_test(tc, hui3);
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