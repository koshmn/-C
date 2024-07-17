#include "../s21_math.h"

long double s21_tan(double x) {
  long double tan;
  if (!S21_IS_INF(x) && !S21_IS_NAN(x)) {
    long double cos = s21_cos(x);
    long double sin = s21_sin(x);
    tan = sin / cos;
  } else
    tan = S21_NAN;
  return tan;
}