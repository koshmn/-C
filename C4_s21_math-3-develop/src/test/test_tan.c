#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_tan(0.0), tan(0.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_tan(-0.0), tan(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  ck_assert_ldouble_nan(tan(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_int_eq(s21_tan(S21_INF_POS), tan(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_int_eq(s21_tan(S21_INF_NEG), tan(S21_INF_NEG));
}
END_TEST

START_TEST(positive_normal) {
  double val = 34.56;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(pi) {
  double val = S21_PI;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(pi_na_2_pochti) {
  double val = S21_PI / 2 + 0.1;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(pi_na_4) {
  double val = S21_PI / 4;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1000000000;
  ck_assert_ldouble_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21;
  ck_assert_ldouble_eq(s21_tan(val), tan(val));
}
END_TEST

START_TEST(negative_normal) {
  double val = -34.56;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(negative_big) {
  double val = -1000000000;
  ck_assert_double_eq_tol(s21_tan(val), tan(val), 0.000001);
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21;
  ck_assert_ldouble_eq(s21_tan(val), tan(val));
}
END_TEST

Suite *s21_tan_cases(void) {
  Suite *suite = suite_create("s21_tan_cases");
  TCase *tc = tcase_create("tan_tc");
  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, minus_zero);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, plus_inf);
  tcase_add_test(tc, negative_inf);
  // стандартные случаи
  tcase_add_test(tc, positive_normal);
  tcase_add_test(tc, pi);
  tcase_add_test(tc, pi_na_2_pochti);
  tcase_add_test(tc, pi_na_4);
  tcase_add_test(tc, positive_big);
  tcase_add_test(tc, positive_little);

  tcase_add_test(tc, negative_normal);
  tcase_add_test(tc, negative_big);
  tcase_add_test(tc, negative_little);

  suite_add_tcase(suite, tc);
  return suite;
}
