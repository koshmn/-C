#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t needle_len = s21_strlen(needle);
  if (needle_len == 0) {
    return (char *)haystack;
  }

  while (*haystack) {
    if (*haystack == *needle) {
      s21_size_t i = 0;
      while (needle[i] && (haystack[i] == needle[i])) {
        i++;
      }
      if (needle[i] == '\0') {
        return (char *)haystack;
      }
    }
    haystack++;
  }
  return s21_NULL;
}