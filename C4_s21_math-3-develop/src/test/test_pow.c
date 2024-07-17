#include "test_runner.h"

START_TEST(number_inf_plus) {
  ck_assert_double_eq(s21_pow(3.0, S21_INF_POS), pow(3.0, S21_INF_POS));
}
END_TEST

START_TEST(number_inf_minus) {
  ck_assert_double_eq(s21_pow(3.0, S21_INF_NEG), pow(3.0, S21_INF_NEG));
}
END_TEST

START_TEST(number_nun) {
  ck_assert_double_nan(s21_pow(3.0, S21_NAN));
  ck_assert_double_nan(pow(3.0, S21_NAN));
}
END_TEST

START_TEST(nun_inf_minus) {
  ck_assert_double_nan(s21_pow(S21_NAN, S21_INF_NEG));
  ck_assert_double_nan(pow(S21_NAN, S21_INF_NEG));
}
END_TEST

START_TEST(nun_inf_plus) {
  ck_assert_double_nan(s21_pow(S21_NAN, S21_INF_POS));
  ck_assert_double_nan(pow(S21_NAN, S21_INF_POS));
}
END_TEST

START_TEST(inf_minus_number) {
  ck_assert_double_eq(s21_pow(S21_INF_NEG, 3.0), pow(S21_INF_NEG, 3.0));
}
END_TEST

START_TEST(inf_plus_number) {
  ck_assert_double_eq(s21_pow(S21_INF_POS, 3.0), pow(S21_INF_POS, 3.0));
}
END_TEST

START_TEST(nun_number) {
  ck_assert_double_nan(s21_pow(S21_NAN, 3.0));
  ck_assert_double_nan(pow(S21_NAN, 3.0));
}
END_TEST

START_TEST(nan_value) {
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_nan(pow(S21_NAN, S21_NAN));
}
END_TEST

START_TEST(zero_zero) { ck_assert_double_eq(s21_pow(0.0, 0.0), pow(0.0, 0.0)); }
END_TEST

START_TEST(negative_inf) {
  ck_assert_double_eq(s21_pow(S21_INF_NEG, S21_INF_NEG),
                      pow(S21_INF_NEG, S21_INF_NEG));
}
END_TEST

START_TEST(positive_inf) {
  ck_assert_double_eq(s21_pow(S21_INF_POS, S21_INF_POS),
                      pow(S21_INF_POS, S21_INF_POS));
}
END_TEST

START_TEST(positive_normal) {
  double val = 3.56;
  double val2 = 1.12;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e21;
  double val2 = 4;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(positive_big_boos) {
  double val = 3.2;
  double val2 = 7000;
  ck_assert_double_eq(s21_pow(val, val2), pow(val, val2));
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21 * S21_PI;
  double val2 = 1e-21 * S21_E;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_1) {
  double val = -3.56;
  double val2 = 2.0;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_2) {
  double val = 3.56;
  double val2 = -2.1;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_3) {
  double val = -3.56;
  double val2 = -2.0;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_big) {
  double val = -1e4 * 123.4321;
  double val2 = -1e4 * 2.0;
  ck_assert_double_eq_tol(s21_pow(val, val2), pow(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-4 * 123.4321;
  double val2 = -1e-4 * 123.4321;
  ck_assert_double_nan(s21_pow(val, val2));
  ck_assert_double_nan(pow(val, val2));
}
END_TEST

START_TEST(one_positive) {
  double val = 1;
  double val2 = 1;
  ck_assert_double_eq(s21_pow(val, val2), pow(val, val2));
}
END_TEST

START_TEST(one_negative) {
  double val = -1;
  double val2 = -1;
  ck_assert_double_eq(s21_pow(val, val2), pow(val, val2));
}
END_TEST

START_TEST(ex) {
  ck_assert_double_eq(s21_pow(S21_INF_POS, 0 / -1), pow(S21_INF_POS, 0 / -1));
}
END_TEST

START_TEST(ex1) {
  ck_assert_double_eq(s21_pow(S21_NAN, 0 / -1), pow(S21_NAN, 0 / -1));
}
END_TEST
START_TEST(ex2) { ck_assert_double_eq(s21_pow(0, 0 / -1), pow(0, 0 / -1)); }
END_TEST

Suite *s21_pow_cases(void) {
  Suite *suite = suite_create("s21_pow_cases");
  TCase *tc = tcase_create("pow_tc");

  // краевые случаи
  tcase_add_test(tc, number_inf_plus);
  tcase_add_test(tc, number_inf_minus);
  tcase_add_test(tc, number_nun);
  tcase_add_test(tc, nun_inf_minus);
  tcase_add_test(tc, nun_inf_plus);
  tcase_add_test(tc, inf_minus_number);
  tcase_add_test(tc, inf_plus_number);
  tcase_add_test(tc, nun_number);
  tcase_add_test(tc, nan_value);
  tcase_add_test(tc, zero_zero);
  tcase_add_test(tc, negative_inf);
  tcase_add_test(tc, positive_inf);
  tcase_add_test(tc, ex);
  tcase_add_test(tc, ex1);
  tcase_add_test(tc, ex2);

  // стандартные случаи
  tcase_add_test(tc, positive_normal);
  tcase_add_test(tc, positive_big);
  tcase_add_test(tc, positive_big_boos);
  tcase_add_test(tc, positive_little);

  tcase_add_test(tc, negative_normal_1);
  tcase_add_test(tc, negative_normal_2);
  tcase_add_test(tc, negative_normal_3);
  tcase_add_test(tc, negative_big);
  tcase_add_test(tc, negative_little);

  tcase_add_test(tc, one_positive);
  tcase_add_test(tc, one_negative);

  suite_add_tcase(suite, tc);
  return suite;
}