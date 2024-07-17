#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = s21_NULL;
  s21_size_t str_len = (s21_strlen(str));
  s21_size_t src_len = (s21_strlen(src));

  if (src != s21_NULL && str != s21_NULL && (src_len >= start_index)) {
    s21_size_t full_len = str_len + src_len;
    new_str = malloc(sizeof(char) * (full_len + 1));
    if (new_str) {
      s21_size_t a = 0, count = 0;
      for (s21_size_t i = 0; i < full_len; i++) {
        if (i < start_index) {
          new_str[i] = src[i];
        } else if (i >= start_index && count < str_len) {
          new_str[i] = str[i - start_index];
          count++;
        } else if (i < full_len) {
          new_str[i] = src[start_index + a];
          a++;
        }
      }
      new_str[full_len] = '\0';
    }
  }
  return new_str;
}