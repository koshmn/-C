#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = s21_strlen(dest);
  s21_size_t j = 0;

  while ((j < n) && (*(src + j) != '\0')) {
    *(dest + i) = *(src + j);
    i += 1;
    j += 1;
  }
  *(dest + i) = '\0';
  return (dest);
}