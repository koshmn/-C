#include "../s21_math.h"

long double s21_log(double x) {
  long double result = S21_INF_NEG;
  if (S21_IS_NAN(x) || x < 0) {
    result = S21_NAN;
  } else if (x == S21_INF_POS) {
    result = x;
  }
  if (x > 0 && x != S21_INF_POS) {
    if (x == 1) {
      result = 0;
    } else {
      if (x <= 2) {
        x -= 1;
        long double number1 = x;
        long double number2 = number1 * x;
        int i = 1;
        long double result_prev = number1 - number2 / (double)(i + 1);
        i += 2;
        number1 = number2 * x;
        number2 = number1 * x;
        result = number1 / (double)i - number2 / (double)(i + 1) + result_prev;
        for (i = 5; s21_fabs(result - result_prev) >= S21_EPS; i += 2) {
          result_prev = result;
          number1 = number2 * x;
          number2 = number1 * x;
          result =
              number1 / (double)i - number2 / (double)(i + 1) + result_prev;
        }
      }
    }
    if (x > 2) {
      x = (x / (x - 1));
      long double number = x;
      int i = 1;
      long double result_prev = 1 / number;
      number = number * x;
      result = 1 / (number * (double)(i + 1)) + result_prev;
      for (i = 3; s21_fabs(result - result_prev) >= S21_EPS; i++) {
        result_prev = result;
        number = number * x;
        result = 1 / (number * (double)i) + result_prev;
      }
    }
  }
  return result;
}