#include "../s21_math.h"

long double s21_step_sin(int n, double x) { return (x * x) / (n * (n - 1)); }

long double s21_sin(double x) {
  long double result;
  if (!S21_IS_INF(x)) {
    x = (double)s21_fmod(x, 2 * S21_PI);
    long double prev_result = x, next_number = (x * x * x) / (2 * 3);
    result = prev_result - next_number;
    int step = 5;
    int sign = 1;
    while (s21_fabs((double)(result - prev_result)) >= S21_EPS) {
      prev_result = result;
      next_number *= s21_step_sin(step, x);
      result += (next_number * sign);
      sign = -sign;
      step += 2;
    }
  } else
    result = S21_NAN;
  return result;
}
