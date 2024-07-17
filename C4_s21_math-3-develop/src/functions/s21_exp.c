#include "../s21_math.h"

long double s21_step_exp(int n, double x) { return x / n; }

long double s21_exp(double x) {
  long double result = 0;
  if (x != S21_INF_NEG) {
    bool neg = x < 0;
    x = (double)s21_fabs(x);
    long double prev_result = 1, next_series_member = x;
    result = prev_result + next_series_member;
    int step = 2;
    while (s21_fabs((double)(result - prev_result)) >= S21_EPS) {
      prev_result = result;
      next_series_member *= s21_step_exp(step, x);
      result += next_series_member;
      step++;
    }
    result = neg ? 1 / result : result;
  }
  return result;
}