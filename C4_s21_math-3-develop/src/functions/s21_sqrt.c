#include "../s21_math.h"

long double s21_sqrt(double x) {
  long double answer = 0.0;
  if (x > 0 && x != S21_INF_POS) {
    double left = 0, right = (x < 1.0) ? 1.0 : x;
    bool was_computed = false;
    while (!was_computed) {
      double approximation = (left + right) / 2;
      if (approximation * approximation <= x) {
        if (approximation == left) {
          answer = approximation;
          was_computed = true;
        }
        left = approximation;
      } else {
        if (approximation == right) {
          answer = approximation;
          was_computed = true;
        }
        right = approximation;
      }
    }
  } else if (x == S21_INF_POS)
    answer = S21_INF_POS;
  else if (x != 0.0)
    answer = S21_NAN;

  return answer;
}