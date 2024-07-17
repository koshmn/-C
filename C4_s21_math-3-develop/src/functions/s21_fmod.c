#include "../s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = S21_NAN;
  if (y != 0 && !S21_IS_NAN(y) && !S21_IS_NAN(x) && !S21_IS_INF(x)) {
    bool neg = x < 0;
    result = s21_fabs(x);
    x = (double)result;
    y = (double)s21_fabs(y);
    long double k = 1e22;
    while (k > 1) {
      if ((x - k * y) >= 0) {
        x -= (double)(k * y);
      } else {
        k /= 10;
      }
    }

    while ((x - y) >= 0) {
      x -= y;
    }
    result = x;
    result = neg ? (-1) * result : result;
  }
  return result;
}