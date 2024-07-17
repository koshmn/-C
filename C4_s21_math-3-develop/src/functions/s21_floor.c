#include "../s21_math.h"

long double s21_floor(double x) {
  long double result;
  if (S21_IS_NAN(x) || S21_IS_INF(x)) {
    result = x;
  } else {
    result = (long long int)x;
    result = (long double)(((x - result) && x < 0) ? result - 1 : result);
  }
  return result;
}