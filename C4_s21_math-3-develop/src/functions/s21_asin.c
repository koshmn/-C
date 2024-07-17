#include "../s21_math.h"

long double s21_step_asin(int n, double x) {
  return ((2 * n - 1) * (2 * n - 1) * x * x) / (2 * n * (2 * n + 1));
}

long double s21_asin(double x) {
  long double result = 0.0;
  if (s21_fabs(x) > 1.0 || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else if (x == 1.0) {
    result = S21_PI / 2;
  } else if (x == -1.0) {
    result = -S21_PI / 2;
  } else if (s21_fabs(x) < S21_EPS) {
    result = x;
  } else {
    long double term = x;
    int n = 1;
    while (s21_fabs((double)term) > S21_EPS) {
      result += term;
      term *= s21_step_asin(n, x);
      n++;
    }
  }
  return result;
}
