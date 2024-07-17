#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_sqrt(0.0), sqrt(0.0)); }
END_TEST

START_TEST(one) { ck_assert_ldouble_eq(s21_sqrt(1.0), sqrt(1.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_sqrt(-0.0), sqrt(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
  ck_assert_ldouble_nan(sqrt(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_ldouble_eq(s21_sqrt(S21_INF_POS), sqrt(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_int_eq(s21_sqrt(S21_INF_NEG), sqrt(S21_INF_NEG));
}
END_TEST

START_TEST(positive_normal) {
  double val = 34.56;
  ck_assert_double_eq_tol(s21_sqrt(val), sqrt(val), 0.000001);
}
END_TEST

START_TEST(prosto_16) {
  double val = 16;
  ck_assert_double_eq_tol(s21_sqrt(val), sqrt(val), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e21;
  ck_assert_ldouble_eq_tol(s21_sqrt(val), sqrt(val), 0.000001);
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21;
  ck_assert_ldouble_eq_tol(s21_sqrt(val), sqrt(val), 0.0000001);
}
END_TEST

START_TEST(negative_normal) {
  double val = -34.56;
  ck_assert_int_eq(s21_sqrt(val), sqrt(val));
}
END_TEST

START_TEST(negative_big) {
  double val = -1e21;
  ck_assert_int_eq(s21_sqrt(val), sqrt(val));
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21;
  ck_assert_int_eq(s21_sqrt(val), sqrt(val));
}
END_TEST

Suite *s21_sqrt_cases(void) {
  Suite *suite = suite_create("s21_sqrt_cases");
  TCase *tc = tcase_create("sqrt_tc");
  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, one);
  tcase_add_test(tc, minus_zero);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, plus_inf);
  tcase_add_test(tc, negative_inf);
  // стандартные случаи
  tcase_add_test(tc, positive_normal);
  tcase_add_test(tc, prosto_16);
  tcase_add_test(tc, positive_big);
  tcase_add_test(tc, positive_little);

  tcase_add_test(tc, negative_normal);
  tcase_add_test(tc, negative_big);
  tcase_add_test(tc, negative_little);

  suite_add_tcase(suite, tc);
  return suite;
}
