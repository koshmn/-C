#include "../s21_math.h"

long double s21_acos(double x) {
  double result;
  if (s21_fabs(x) > 1.0 || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else {
    result = S21_PI / 2 - s21_asin(x);
  }
  return result;
}
