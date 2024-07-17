#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  unsigned char ch = c;
  for (s21_size_t i = 0; i < n; ++i) {
    if (p[i] == ch) {
      return (void *)(p + i);
    }
  }
  return s21_NULL;
}