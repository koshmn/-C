#include "test_runner.h"

START_TEST(zero) { ck_assert_int_eq(s21_abs(0), abs(0)); }
END_TEST

START_TEST(minus_zero) { ck_assert_int_eq(s21_abs(-0), abs(-0)); }
END_TEST

START_TEST(positive_normal) {
  int val = 5;
  ck_assert_int_eq(s21_abs(val), abs(val));
}
END_TEST

START_TEST(negative_normal) {
  int val = -5;
  ck_assert_int_eq(s21_abs(val), abs(val));
}
END_TEST

START_TEST(one_positive) {
  int val = 1;
  ck_assert_int_eq(s21_abs(val), abs(val));
}
END_TEST

START_TEST(one_negative) {
  int val = -1;
  ck_assert_int_eq(s21_abs(val), abs(val));
}
END_TEST

Suite *s21_abs_cases(void) {
  Suite *suite = suite_create("s21_abs_cases");
  TCase *tc = tcase_create("abs_tc");

  // краевые случаи
  tcase_add_test(tc, zero);
  tcase_add_test(tc, minus_zero);
  // стандартные случаи
  tcase_add_test(tc, positive_normal);

  tcase_add_test(tc, negative_normal);

  tcase_add_test(tc, one_positive);
  tcase_add_test(tc, one_negative);

  suite_add_tcase(suite, tc);
  return suite;
}
