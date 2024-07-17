#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *char_dest = (char *)dest;
  const char *char_src = (char *)src;
  while (n--) {
    *char_dest++ = *char_src++;
  }
  return dest;
}
