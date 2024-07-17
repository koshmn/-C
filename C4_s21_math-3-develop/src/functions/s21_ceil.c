#include "../s21_math.h"

long double s21_ceil(double x) {
  long double result;
  if (S21_IS_NAN(x)) {
    result = S21_NAN;
  } else if (S21_IS_INF(x)) {
    result = x;
  } else {
    int intPart = (int)x;
    if (x == intPart) {
      result = x;
    } else if (x > 0) {
      result = intPart + 1;
    } else {
      result = intPart;
    }
  }
  return result;
}
