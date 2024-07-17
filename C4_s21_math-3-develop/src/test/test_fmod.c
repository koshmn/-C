#include "test_runner.h"

START_TEST(number_inf_plus) {
  ck_assert_ldouble_eq(s21_fmod(3.0, S21_INF_POS), fmod(3.0, S21_INF_POS));
}
END_TEST

START_TEST(number_inf_minus) {
  ck_assert_ldouble_eq(s21_fmod(3.0, S21_INF_NEG), fmod(3.0, S21_INF_NEG));
}
END_TEST

START_TEST(number_nun) {
  ck_assert_ldouble_nan(s21_fmod(3.0, S21_NAN));
  ck_assert_ldouble_nan(fmod(3.0, S21_NAN));
}
END_TEST

START_TEST(nun_inf_minus) {
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_INF_NEG));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_INF_NEG));
}
END_TEST

START_TEST(nun_inf_plus) {
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_INF_POS));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_INF_POS));
}
END_TEST

START_TEST(inf_minus_number) {
  ck_assert_ldouble_nan(s21_fmod(S21_INF_NEG, 3.0));
  ck_assert_ldouble_nan(fmod(S21_INF_NEG, 3.0));
}
END_TEST

START_TEST(inf_plus_number) {
  ck_assert_ldouble_nan(s21_fmod(S21_INF_POS, 3.0));
  ck_assert_ldouble_nan(fmod(S21_INF_POS, 3.0));
}
END_TEST

START_TEST(nun_number) {
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, 3.0));
  ck_assert_ldouble_nan(fmod(S21_NAN, 3.0));
}
END_TEST

START_TEST(nan_value) {
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_NAN));
}
END_TEST

START_TEST(zero_zero) {
  ck_assert_ldouble_nan(s21_fmod(0.0, 0.0));
  ck_assert_ldouble_nan(fmod(0.0, 0.0));
}
END_TEST

START_TEST(negative_inf) {
  ck_assert_ldouble_nan(s21_fmod(S21_INF_NEG, S21_INF_NEG));
  ck_assert_ldouble_nan(fmod(S21_INF_NEG, S21_INF_NEG));
}
END_TEST

START_TEST(positive_inf) {
  ck_assert_ldouble_nan(s21_fmod(S21_INF_POS, S21_INF_POS));
  ck_assert_ldouble_nan(fmod(S21_INF_POS, S21_INF_POS));
}
END_TEST

START_TEST(positive_normal) {
  double val = 3.56;
  double val2 = 1.12;
  ck_assert_double_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(positive_big) {
  double val = 1e21;
  double val2 = 10;
  ck_assert_ldouble_eq(s21_fmod(val, val2), fmod(val, val2));
}
END_TEST

START_TEST(positive_little) {
  double val = 1e-21 * S21_PI;
  double val2 = 1e-21 * S21_E;
  ck_assert_ldouble_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_1) {
  double val = -3.56;
  double val2 = 2.0;
  ck_assert_double_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_2) {
  double val = 3.56;
  double val2 = -2.0;
  ck_assert_double_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_normal_3) {
  double val = -3.56;
  double val2 = -2.0;
  ck_assert_double_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_big) {
  double val = -1e21 * 123.4321;
  double val2 = -1e20 * 2.0;
  ck_assert_ldouble_eq_tol(s21_fmod(val, val2), fmod(val, val2), 0.000001);
}
END_TEST

START_TEST(negative_little) {
  double val = -1e-21 * 123.4321;
  double val2 = -1e-19 * 123.4321;
  ck_assert_ldouble_eq(s21_fmod(val, val2), fmod(val, val2));
}
END_TEST

START_TEST(one_positive) {
  double val = 1;
  double val2 = 1;
  ck_assert_double_eq(s21_fmod(val, val2), fmod(val, val2));
}
END_TEST

START_TEST(one_negative) {
  double val = -1;
  double val2 = -1;
  ck_assert_double_eq(s21_fmod(val, val2), fmod(val, val2));
}
END_TEST

Suite *s21_fmod_cases(void) {
  Suite *suite = suite_create("s21_fmod_cases");
  TCase *tc = tcase_create("fmod_tc");

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
  // стандартные случаи
  tcase_add_test(tc, positive_normal);
  tcase_add_test(tc, positive_big);
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