#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *a, *b;
  for (a = str1; *a != '\0'; ++a) {
    for (b = str2; *b != '\0'; ++b) {
      if (*a == *b) {
        return (void *)(a);
      }
    }
  }
  return s21_NULL;
}