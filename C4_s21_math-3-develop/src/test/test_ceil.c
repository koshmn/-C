#include "test_runner.h"

START_TEST(zero) { ck_assert_ldouble_eq(s21_ceil(0.0), ceil(0.0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_ldouble_eq(s21_ceil(-0.0), ceil(-0.0)); }
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
  ck_assert_ldouble_nan(ceil(S21_NAN));
}
END_TEST

START_TEST(plus_inf) {
  ck_assert_ldouble_eq(s21_ceil(S21_INF_POS), ceil(S21_INF_POS));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_ldouble_eq(s21_ceil(S21_INF_NEG), ceil(S21_INF_NEG));
}
END_TEST

START_TEST(positive_normal) {
  double val = 34.56;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

START_TEST(positive_big) {
  double val = 1e9;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

START_TEST(negative_normal) {
  double val = -34.56;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

START_TEST(negative_big) {
  double val = -1e9;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21;
  ck_assert_ldouble_eq(s21_ceil(val), ceil(val));
}
END_TEST

Suite *s21_ceil_cases(void) {
  Suite *suite = suite_create("s21_ceil_cases");
  TCase *tc = tcase_create("ceil_tc");
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

  tcase_add_test(tc, negative_normal);
  tcase_add_test(tc, negative_big);
  tcase_add_test(tc, negative_little);

  suite_add_tcase(suite, tc);
  return suite;
}
