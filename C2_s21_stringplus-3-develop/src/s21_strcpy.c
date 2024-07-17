#include "s21_string.h"

char *s21_strcpy(char *s, const char *t) {
  while (*t != '\0') *(s++) = *(t++);
  return s;
}
