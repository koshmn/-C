#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *str_temp = s21_NULL;
  int flag = 0;
  if (str == s21_NULL) {
    str = str_temp;
  } else {
    str_temp = str;
  }
  if (str == s21_NULL) {
    flag++;
  }
  if (flag == 0) {
    while (*str && s21_strpbrk(str, delim) == str) {
      str++;
    }
    if (*str == '\0' && flag == 0) {
      flag++;
    }
    if (flag == 0) {
      char *last_char = s21_strpbrk(str, delim);
      if (last_char) {
        *last_char = '\0';
        str_temp = last_char + 1;
      } else {
        str_temp = s21_NULL;
      }
    } else {
      str = s21_NULL;
    }
  } else {
    str = s21_NULL;
  }
  return str;
}
