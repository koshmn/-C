#include "../s21_math.h"

long double s21_cos(double x) {
  long double result;
  if (S21_IS_INF(x) || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else {
    x = (double)s21_fmod(x, 2 * S21_PI);
    result = 1;
    long double prev_result = 0;
    long double term = -x * x / 2;
    int n;
    for (n = 1; s21_fabs((double)(prev_result - result)) >= S21_EPS / 2; ++n) {
      prev_result = result;
      result += term;
      term *= -(x * x / ((2 * n + 1) * (2 * n + 2)));
    }
  }
  return result;
}
