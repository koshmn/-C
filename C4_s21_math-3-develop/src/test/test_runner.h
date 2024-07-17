#ifndef TEST_RUNNER_H_
#define TEST_RUNNER_H_

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_math.h"

#define S21_E 2.7182818284590452353602874713526624977572

#define SEP "|================================|"

Suite *s21_atan_cases(void);
Suite *s21_ceil_cases(void);
Suite *s21_cos_cases(void);
Suite *s21_fabs_cases(void);
Suite *s21_exp_cases(void);
Suite *s21_floor_cases(void);
Suite *s21_abs_cases(void);
Suite *s21_acos_cases(void);
Suite *s21_asin_cases(void);
Suite *s21_sin_cases(void);
Suite *s21_sqrt_cases(void);
Suite *s21_tan_cases(void);
Suite *s21_log_cases(void);
Suite *s21_pow_cases(void);
Suite *s21_fmod_cases(void);

#endif  // TEST_RUNNER_H_
