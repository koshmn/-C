#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *a, *b;
  s21_size_t length = 0;
  for (a = str1; *a != '\0'; ++a) {
    for (b = str2; *b != '\0'; ++b) {
      if (*a == *b) {
        return length;
      }
    }
    ++length;
  }
  return length;
}