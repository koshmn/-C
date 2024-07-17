#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *cp_str = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    cp_str = malloc(sizeof(char) * (len + 1));
    if (cp_str) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          cp_str[i] = str[i] + 32;
        } else
          cp_str[i] = str[i];
      }
      cp_str[len] = '\0';
    }
  }
  return cp_str;
}