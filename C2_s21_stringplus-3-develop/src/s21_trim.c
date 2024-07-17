#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;
  if (src && trim_chars) {
    s21_size_t src_len = (s21_strlen(src));
    s21_size_t trim_chars_len = (s21_strlen(trim_chars));
    s21_size_t match_left = 0, match_right = 0, flag_left = 1, flag_right = 1;

    for (s21_size_t i = 0; i < src_len; i++) {
      for (s21_size_t m = 0; m < trim_chars_len; m++) {
        if (i <= match_left) {
          if (trim_chars[m] == src[i]) {
            match_left++;
          }
        } else {
          flag_left = 0;
          break;
        }
      }
      if (flag_left == 0) break;
    }

    char *return_src = s21_NULL;
    return_src = malloc(sizeof(char) * (src_len + 1));
    for (s21_size_t i = 0, j = src_len - 1; i < src_len; i++, j--) {
      return_src[i] = src[j];
    }

    for (s21_size_t i = 0; i < src_len; i++) {
      for (s21_size_t m = 0; m < trim_chars_len; m++) {
        if (i <= match_right) {
          if (trim_chars[m] == return_src[i]) {
            match_right++;
          }
        } else {
          flag_right = 0;
          break;
        }
      }
      if (flag_right == 0) break;
    }

    free(return_src);

    s21_size_t new_str_len = src_len - (match_left + match_right);
    new_str = malloc(sizeof(char) * (new_str_len + 1));

    for (s21_size_t i = 0; i < new_str_len; i++, match_left++) {
      new_str[i] = src[match_left];
    }
    new_str[new_str_len] = '\0';
  }
  return new_str;
}