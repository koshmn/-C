#include "../s21_math.h"

long double s21_atan_step(long double x, int n, bool deg) {
  return -(deg ? x * x : 1.0 / x / x) * (2 * n + 1) / (2 * n + 3);
}

long double s21_atan(double x) {
  long double atan;
  if (x == S21_INF_POS) {
    atan = S21_PI / 2;
  } else if (x == S21_INF_NEG) {
    atan = -S21_PI / 2;
  } else if (x == 1) {
    atan = S21_PI / 4;
  } else if (x == -1) {
    atan = -S21_PI / 4;
  } else {
    bool in_interval = (s21_fabs(x) < 1.0);
    atan = in_interval ? x : 1.0 / x;
    long double prev_res = 0, member = atan * s21_atan_step(x, 0, in_interval);
    for (int n = 1; s21_fabs((double)(prev_res - atan)) > S21_EPS; ++n) {
      prev_res = atan;
      atan += member;
      member *= s21_atan_step(x, n, in_interval);
    }
    atan = in_interval ? atan : ((S21_PI * s21_fabs(x) / (2 * x)) - atan);
  }
  return atan;
}
