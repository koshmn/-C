#include "../s21_math.h"

typedef struct {
  long double b;
  long double pow;
} pow_t;

void pow_integer(pow_t *p, double a) {
  while (p->b >= 1) {
    p->pow *= a;
    p->b--;
  }
}

void pow_fractional(pow_t *p, double a, double b) {
  while (p->b > 0) {
    if (b <= p->b) {
      p->b -= b;
      p->pow *= a;
    }
    a = s21_sqrt(a);
    b /= 2;
  }
}

long double s21_pow(double a, double b) {
  pow_t p = {s21_fabs(b), 1};
  if ((!S21_IS_NAN(a) && !S21_IS_INF(a)) &&
      (!S21_IS_NAN(b) && !S21_IS_INF(b))) {
    p.pow = 1;
    bool znak = b >= 0 ? true : false;
    pow_integer(&p, a);
    pow_fractional(&p, a, 1);
    if (!znak) {
      p.pow = 1 / p.pow;
    }
  }
  if (a < 0 && s21_fabs(b) < 1) {
    p.pow = S21_NAN;
  }
  if ((b == S21_INF_POS || S21_IS_NAN(b)) && !S21_IS_NAN(a)) {
    p.pow = b;
  }
  if (b == S21_INF_NEG && !S21_IS_NAN(a)) {
    p.pow = 0;
  }
  if (S21_IS_NAN(a) && b != 0) {
    p.pow = a;
  }
  if (S21_IS_INF(a) && b != 0 && !S21_IS_INF(b)) {
    p.pow = a;
  }
  return p.pow;
}
