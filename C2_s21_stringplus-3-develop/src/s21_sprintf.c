//#include "s21_sprintf.h"

#include <stdio.h>

#include "s21_string.h"

char *s21_strcat(char *str1, const char *str2);
void obnull(char *buffer) {
  for (int i = 0; i < BUFF; i++) {
    buffer[BUFF] = '\0';
  }
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int s21_sprintf(char *str, const char *format, ...) {
  flags f = {0};
  va_list va;
  va_start(va, format);
  char *char_string = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    }

    format = get_flags(format, &f);
    format = get_width(format, &f, va);
    format = get_precision(format, &f, va);
    format = get_length(format, &f);

    f.specificator = *format;
    format++;

    char buffer[BUFF] = {'\0'};
    writing(f, buffer, va);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];
  }

  *str = '\0';
  va_end(va);
  return str - char_string;
}

const char *get_flags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, flags *f, va_list va) {
  if (*format == '*') {
    format++;
    f->width = va_arg(va, int);
  } else if (is_digit(*format)) {
    char tmp[BUFF] = {'\0'};
    for (int i = 0; is_digit(*format); i++, format++) tmp[i] = *format;
    f->width = atoi(tmp);
  }
  return format;
}

const char *get_precision(const char *format, flags *f, va_list va) {
  if (*format == '.') {
    f->is_precision = 1;
    format++;
  }

  if (*format == '*') {
    format++;
    f->precision = va_arg(va, int);
  }
  if (is_digit(*format)) {
    char tmp[BUFF] = {'\0'};
    for (int i = 0; is_digit(*format); i++, format++) tmp[i] = *format;
    f->precision = atoi(tmp);
  }
  return format;
}

const char *get_length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
  }
  return format;
}

void num_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF] = {'\0'};
  int index = BUFF - 2;

  int neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[index] = '0';

  while (val > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[index]; index++, j++) {
    if (neg && j == 0) {
      ret[j++] = '-';
    }

    ret[j] = tmp[index];
  }
}

void format_precision(char *buffer, flags f) {
  char tmp[BUFF] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buffer);

  if (buffer[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.precision > len) {
    int index;
    for (index = sign; index < f.precision - len + sign; index++)
      tmp[index] = '0';

    for (int i = sign; buffer[i]; i++, index++) tmp[index] = buffer[i];

    s21_strcpy(buffer, tmp);
  }

  if (f.is_precision && f.precision == 0 && int_flags(f.specificator) &&
      buffer[0] == '0')
    buffer[0] = '\0';
}

int int_flags(char c) {
  char flagi[] = {'d', 'i', 'u'};
  int res = 0;
  for (s21_size_t i = 0; i < sizeof(flagi); i++) {
    if (flagi[i] == c) {
      res = 1;
      break;
    }
  }
  return res;
}

void format_flags(char *buffer, flags f) {
  char tmp[BUFF + 1] = {'\0'};
  if (f.plus && f.specificator != 'u') {
    tmp[0] = buffer[0] == '-' ? buffer[0] : '+';
    s21_strcpy(tmp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, tmp);
  } else if (f.space && buffer[0] != '-' && f.specificator != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buffer);
    s21_strcpy(buffer, tmp);
  }
  if (f.width > (int)s21_strlen(buffer)) {
    int index = f.width - s21_strlen(buffer);
    if (!f.minus) {
      s21_memset(tmp, ' ', index);
      s21_strcpy(tmp + index, buffer);
    } else {
      s21_strcpy(tmp, buffer);
      s21_memset(tmp + s21_strlen(tmp), ' ', index);
    }
    s21_strcpy(buffer, tmp);
  }
}

void unum_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF + 1] = {'\0'};
  int index = BUFF - 1;
  if (val == 0) {
    buf[index] = '0';
    index--;
  }

  while (val && index) {
    buf[index] = "0123456789abcdef"[val % base];
    --index;
    val /= base;
  }
  for (int j = 0; buf[index + 1]; index++, j++) ret[j] = buf[index + 1];
}

void parse_uint(flags f, char *buffer, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unum_to_string(val, buffer, 10);
  format_precision(buffer, f);
  format_flags(buffer, f);
}

void parse_int(flags f, char *buffer, va_list va) {
  int64_t val = va_arg(va, int64_t);

  switch (f.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
      break;
  }
  num_to_string(val, buffer, 10);
  format_precision(buffer, f);
  format_flags(buffer, f);
}

//___________________ числа дабббл_____________________________________________

void double_to_string(long double number, char *result, flags f) {
  // printf("OK");
  char buffer[BUFF];
  obnull(buffer);
  int index = BUFF - 2;

  // printf("OK");
  int negative = 0;
  if (number < 0) {
    negative = 1;
    number *= -1;
  }

  long double before = 0,
              after = modfl(number, &before);  // before -  целая ater - дробная
  if (f.precision == 0) {
    before = roundl(number);
    after = 0;
  }

  char precision[BUFF];
  obnull(precision);
  for (int i = 0; i < f.precision; i++) {
    after *= 10;
  }
  long long right = roundl(after), left = before;

  if (!right) {
    for (int i = f.precision; i > 0; i++) {
      buffer[index] = '0';
      index--;
    }
  } else {
    for (int i = f.precision; right || i > 0; i--) {
      buffer[index] = (int)(right % 10 + 0.05) + '0';
      right /= 10;
      index--;
    }
  }

  if (((f.is_precision && f.precision != 0) || (int)right == 0 ||
       (!f.is_precision && number == 0)) &&
      f.precision != 0) {
    buffer[index] = '.';
    index--;
    // printf("OK");
  }

  if (!left) {
    buffer[index] = '0';
    index--;
  } else {
    while (left) {
      buffer[index] = (int)(left % 10) + '0';
      left /= 10;
      index--;
    }
  }

  for (int i = 0; buffer[index + 1] != '\0' || index < BUFF - 1;
       i++, index++) {  //!!!!!!!!!!!!!!!проверить даббл ту стринг
    if (i == 0 && negative) {
      result[i] = '-';
      i++;
    }
    result[i] = buffer[index + 1];
  }
}

void parse_double(flags f, char *buffer, va_list va) {
  long double val = 0;
  val = va_arg(va, double);

  if (!f.is_precision) {
    f.precision = 6;
  }

  double_to_string(val, buffer, f);
  format_flags(buffer, f);
}

// ___________________________буковки__________________________________________

void parse_char(flags f, char *buffer, va_list va) {
  if (f.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(va, wchar_t);
    format_wchar(f, buffer, w_c);
  } else {
    char c;
    c = va_arg(va, int);
    format_char(f, buffer, c);
  }
}

void format_wchar(flags f, char *buffer, wchar_t w_c) {
  if (!f.minus && f.width) {
    char tmp[BUFF] = {'\0'};
    wcstombs(tmp, &w_c, BUFF);
    for (s21_size_t i = 0; i < f.width - s21_strlen(tmp); i++) buffer[i] = ' ';
    s21_strcat(buffer, tmp);
  } else if (f.width) {
    wcstombs(buffer, &w_c, BUFF);
    for (int i = s21_strlen(buffer); i < f.width; i++) buffer[i] = ' ';
  } else {
    wcstombs(buffer, &w_c, BUFF);
  }
}
void format_char(flags f, char *buffer, char c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buffer[i] = ' ';
      if (i == f.width - 1) buffer[i] = c;
    }
  } else if (f.width) {
    buffer[0] = c;
    for (int i = 1; i < f.width; i++) buffer[i] = ' ';
  } else {
    buffer[0] = c;
  }
}

void parse_string(flags f, char *buffer, va_list va) {
  if (f.length == 'l') {
    wchar_t *wstr = va_arg(va, wchar_t *);
    format_wide_string(f, buffer, wstr);
  } else {
    char *str = va_arg(va, char *);
    format_string(f, buffer, str);
  }
}
void format_string(flags f, char *buffer, char *str) {
  char tmp[BUFF] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}
void format_wide_string(flags f, char *buffer, wchar_t *wstr) {
  char tmp[BUFF] = {'\0'};
  char str[BUFF] = {'\0'};

  wcstombs(str, wstr, BUFF);
  s21_strcpy(tmp, str);
  if (f.is_precision) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}

//____________писалка в буфер_______________

void writing(flags f, char *buffer, va_list va) {
  if (f.specificator == 'd' || f.specificator == 'i')
    parse_int(f, buffer, va);
  else if (f.specificator == 'u')
    parse_uint(f, buffer, va);
  else if (f.specificator == '%')
    buffer[0] = '%';
  else if (f.specificator == 'c')
    parse_char(f, buffer, va);
  else if (f.specificator == 's')
    parse_string(f, buffer, va);
  else if (f.specificator == 'f')
    parse_double(f, buffer, va);
}

char *s21_strcat(char *str1, const char *str2) {
  while (*str1) {
    str1++;
  }
  while (*str2) {
    *str1 = *str2;
    str1++;
    str2++;
  }
  *str1 = '\0';
  return str1;
}