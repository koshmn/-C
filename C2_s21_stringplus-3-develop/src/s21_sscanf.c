#include "s21_string.h"
int s21_sscanf(const char *str, const char *format, ...) {
  char *o_str = (char *)str;
  char *o_format = (char *)format;
  int valid = 1;
  int kolvo = 0;

  va_list valist = {0};
  va_start(valist, format);

  char *start = o_str;
  while (*o_format && valid) {
    if (*o_format == '%') {
      format_tok token = {0, '0', -1, '1'};
      o_format++;
      if (format_parse(&token, &o_format) == 1) {
        kolvo += str_write(valist, &token, &o_str, start, &valid);
      }
      if (format_valid(&token) == 0) valid = 0;

    } else {
      if (*o_format++ != *o_str) {
        if (*o_format != ' ' && *o_format != '%') valid = 0;
      } else
        o_str++;
    }
  }
  va_end(valist);
  return kolvo;
}

int format_parse(format_tok *token, char **o_format) {
  int flag = 1;
  if (**o_format != '%') {
    flag = format_parse_width(o_format, token);
    format_parse_length(o_format, token);
    format_parse_specifier(o_format, token);
  } else {
    token->specifiers = '%';
    (*o_format)++;
  }
  return flag;
}

int format_parse_width(char **o_format, format_tok *token) {
  int flag = 1;
  if (**o_format == '*') {
    (*o_format)++;
    token->width = -2;
  }

  while (**o_format >= '0' && **o_format <= '9') {  //если число
    if (token->width == -2) {
      flag = 0;
    } else {
      if (token->width == -1)  //первое число
        token->width = (**o_format - '0');
      else
        token->width = token->width * 10 + (**o_format - '0');
    }
    (*o_format)++;
  }
  return flag;
}

void format_parse_length(char **o_format, format_tok *token) {
  switch (**o_format) {
    case 'h':
      token->len = 'h';
      (*o_format)++;
      break;
    case 'l':
      token->len = 'l';
      (*o_format)++;
      break;
    case 'L':
      token->len = 'L';
      (*o_format)++;
      break;
  }
}

void format_parse_specifier(char **o_format, format_tok *token) {
  token->specifiers = (**o_format);
  (*o_format)++;
}

int format_valid(format_tok *token) {
  int flag = 1;
  char specif[] = "cdieEfgGosuxXpn%%";
  char nospech[] = "csfeEGgp";
  char nospecl[] = "p";

  if ((token->len == 'h' &&
       (s21_strchr(nospech, token->specifiers) != s21_NULL)) ||
      (token->len == 'l' &&
       (s21_strchr(nospecl, token->specifiers) != s21_NULL))) {
    flag = 0;
  }
  if (token->specifiers == '%' && token->len != '1') {
    flag = 0;
  }
  if (s21_strchr(specif, token->specifiers) == s21_NULL) {
    flag = 0;
  }

  return flag;
}

int str_write(va_list valist, format_tok *token, char **o_str, char *start,
              int *valid) {
  int kolvo = 0;
  switch (token->specifiers) {
    case 'c':
      if (**o_str != '\0') kolvo += write_c(valist, token, o_str);
      break;
    case 'd':
      kolvo += write_d(valist, token, o_str, valid);
      break;
    case 'i':
      kolvo += write_i(valist, token, o_str);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      kolvo += write_f(valist, token, o_str);
      break;
    case 'o':
      kolvo += write_o(valist, token, o_str, 1);
      break;
    case 's':
      kolvo += write_s(valist, token, o_str);
      break;
    case 'u':
      kolvo += write_u(valist, token, o_str, valid);
      break;
    case 'x':
    case 'X':
      kolvo += write_x(valist, token, o_str, 1);
      break;
    case 'p':
      kolvo += write_p(valist, token, o_str);
      break;
    case 'n':
      *va_arg(valist, long int *) = *o_str - start;
      break;
    case '%':
      write_persent(o_str);
      break;
  }
  return kolvo;
}

int write_c(va_list valist, format_tok *token, char **o_str) {
  int flag = 1;
  if (token->width != -2) {
    if (token->len == 'l') {
      wint_t *ch = va_arg(valist, wint_t *);  //ИЛИ wchar_t*
      *ch = **o_str;
    } else {
      char *ch = va_arg(valist, char *);
      *ch = **o_str;
    }
  }
  if (token->width == -1) token->width = 1;
  while (token->width != 0) {
    (*o_str)++;
    token->width--;
  }
  return flag;
}

int write_d(va_list valist, format_tok *token, char **o_str, int *valid) {
  int flag = 0;
  long int res = 0;
  int n_symbol = 0;
  int flag_atoi = str_atoi(token, o_str, &res, 10, &n_symbol);
  if (flag_atoi == 0)
    *valid = 0;
  else if (token->width != -2) {
    write_var_d(valist, token, res, flag_atoi);
    flag = 1;
  }
  return flag;
}

void write_var_d(va_list valist, format_tok *token, long int res,
                 int flag_atoi) {
  if (token->len == '1') {
    int *d = va_arg(valist, int *);
    if (flag_atoi == 1) *d = (int)res;
  } else if (token->len == 'h') {
    short *d = va_arg(valist, short *);
    if (flag_atoi == 1) *d = (short)res;
  } else if (token->len == 'l') {
    long *d = va_arg(valist, long *);
    if (flag_atoi == 1) *d = (long)res;
  }
}

int write_i(va_list valist, format_tok *token, char **o_str) {
  int flag = 0;
  int multi_sign = 0;
  int n_symbol = 0;
  int sign = find_sign(token, o_str, &multi_sign, &n_symbol);

  if (**o_str == '0') {
    (*o_str)++;
    flag = 1;
    if (**o_str == 'x' || **o_str == 'X') {
      (*o_str)++;
      if (multi_sign > 1) sign = 0;
      write_x(valist, token, o_str, sign);
    } else {
      if (multi_sign > 1) sign = 0;
      write_o(valist, token, o_str, sign);
    }
  } else {
    long int res = 0;
    int flag_atoi = str_atoi(token, o_str, &res, 10, &n_symbol);
    if (multi_sign > 1) flag_atoi = 0;
    if (token->width != -2) {
      flag = 1;
      write_var_d(valist, token, res * sign, flag_atoi);
    }
  }
  return flag;
}

void oct_to_dec(long int number, long int *decimal) {
  int i = 0;

  while (number != 0) {
    *decimal = *decimal + (number % 10) * pow(8, i++);
    number = number / 10;
  }
}

void skip(char **o_str) {
  while (**o_str == ' ' || **o_str == '\n' || **o_str == '\t') {
    (*o_str)++;
  }
}

int write_o(va_list valist, format_tok *token, char **o_str, int sign) {
  int flag = 0;
  long int octal = 0;
  long int decimal = 0;
  int n_symbol = 0;
  skip(o_str);
  int flag_atoi = str_atoi(token, o_str, &octal, 8, &n_symbol);
  if (sign == 0) flag_atoi = 0;

  if (token->width != -2) {
    oct_to_dec(octal, &decimal);
    flag = 1;
    write_var_u(valist, token, decimal * sign, flag_atoi);
  }
  return flag;
}

int write_s(va_list valist, format_tok *token, char **o_str) {
  int flag = 0;
  if (token->width != -2) {
    flag = 1;
    if (token->len == 'l') {
      skip(o_str);
      wchar_t *s = va_arg(valist, wchar_t *);
      while (!((**o_str == '\0' || **o_str == ' ' || **o_str == '\t' ||
                **o_str == '\n') ||
               token->width == 0)) {
        *s++ = **o_str;
        s++;
        (*o_str)++;
        token->width--;
      }
      *s = '\0';
    } else {
      skip(o_str);
      char *s = va_arg(valist, char *);
      while (!((**o_str == '\0' || **o_str == ' ' || **o_str == '\t' ||
                **o_str == '\n') ||
               token->width == 0)) {
        *s = **o_str;
        s++;
        (*o_str)++;
        token->width--;
      }
      *s = '\0';
    }
  } else {
    while (!((**o_str == ' ' || **o_str == '\t' || **o_str == '\n') ||
             token->width == 0)) {
      (*o_str)++;
      token->width--;
    }
  }
  return flag;
}

int write_u(va_list valist, format_tok *token, char **o_str, int *valid) {
  int flag = 0;
  long int res = 0;
  int n_symbol = 0;
  int flag_atoi = str_atoi(token, o_str, &res, 10, &n_symbol);
  if (flag_atoi == 0)
    *valid = 0;
  else if (token->width != -2) {
    flag = 1;
    write_var_u(valist, token, res, flag_atoi);
  }
  return flag;
}

void write_var_u(va_list valist, format_tok *token, long int res,
                 int flag_atoi) {
  if (token->len == '1') {
    unsigned int *u = va_arg(valist, unsigned int *);
    if (flag_atoi == 1) *u = (unsigned int)res;
  } else if (token->len == 'h') {
    unsigned short *u = va_arg(valist, unsigned short *);
    if (flag_atoi == 1) *u = (unsigned short)res;
  } else if (token->len == 'l') {
    unsigned long *u = va_arg(valist, unsigned long *);
    if (flag_atoi == 1) *u = (unsigned long)res;
  }
}

int str_16_atoi(format_tok *token, char **o_str, long int *res) {
  int flag = 1;
  int multi_sign = 0;
  int number = 0;
  int n_symbol = 0;
  int sign = find_sign(token, o_str, &multi_sign, &n_symbol);

  while (token->width != 0 &&
         ((**o_str >= '0' && **o_str <= '9' && token->width != 0) ||
          (**o_str >= 'a' && **o_str <= 'f' && token->width != 0) ||
          (**o_str >= 'A' && **o_str <= 'F' && token->width != 0))) {
    (*o_str)++;
    number++;
    if (token->width > -1) token->width--;
  }

  for (int i = 0; i < number; i++) {
    (*o_str)--;
    *res += to_digit(**o_str) * pow(16, i);
  }
  (*o_str) += number;

  *res *= sign;
  if (multi_sign > 1 || number == 0) flag = 0;
  return flag;
}

long int to_digit(char c) {
  long int res;

  if (c <= '9') {
    res = c - '0';
  } else if (c <= 'A' + 16 - 10) {
    res = c - 'A' + 10;
  } else {
    res = c - 'a' + 10;
  }
  return res;
}

int write_x(va_list valist, format_tok *token, char **o_str, int sign) {
  int flag = 0;
  long int decimal = 0;
  skip(o_str);
  if (**o_str == '0') {
    (*o_str)++;
  }
  if (**o_str == 'x') {
    (*o_str)++;
  }
  int flag_atoi = str_16_atoi(token, o_str, &decimal);
  if (sign == 0) flag_atoi = 0;

  if (token->width != -2) {
    flag = 1;
    write_var_u(valist, token, decimal * sign, flag_atoi);
  }
  return flag;
}

int write_p(va_list valist, format_tok *token, char **o_str) {
  int flag = 0;
  long int decimal = 0;

  if (**o_str == '0') {
    (*o_str)++;
  }
  if (**o_str == 'x') {
    (*o_str)++;
  }
  str_16_atoi(token, o_str, &decimal);
  if (token->width != -2) {
    void **p = va_arg(valist, void **);
    *p = (void *)(0x0 + decimal);
    flag = 1;
  }
  return flag;
}

int write_f(va_list valist, format_tok *token, char **o_str) {
  int flag = 0;
  long int left = 0;
  int check = 0;
  int multi_sign = 0;
  int n_symbol = 0;
  int sign = find_sign(token, o_str, &multi_sign, &n_symbol);
  int flag_atoi = str_atoi(token, o_str, &left, 10, &n_symbol);
  if (multi_sign > 1) flag_atoi = 0;

  long double number = 0;
  if (token->width != 0) {
    switch (**o_str) {
      case '.':
        (*o_str)++;
        token->width--;
        long int right = 0;
        str_atoi(token, o_str, &right, 10, &n_symbol);
        while (right > 0) {
          number += (right % 10);
          number *= 0.1;
          right /= 10;
        }
        if (left < 0)
          number += -1 * left;
        else
          number += left;
        if (sign == -1) number *= -1;

        if (**o_str == 'e' || **o_str == 'E') {
          number = scan_e(token, o_str, number);
        }
        break;

      case 'e':
      case 'E':
        number = scan_e(token, o_str, left);
        break;
      default:
        if (flag_atoi) {
          check = 1;
          flag = 1;
          write_var_f(valist, token, left * sign, flag_atoi);
        }
        break;
    }
    if (flag_atoi && check == 0) {
      flag = 1;
      write_var_f(valist, token, number, flag_atoi);
    }
  } else if (flag_atoi) {
    write_var_f(valist, token, left * sign, flag_atoi);
    flag = 1;
  }
  return flag;
}

long double scan_e(format_tok *token, char **o_str, long double number) {
  (*o_str)++;
  token->width--;

  long int power = 0;
  int n_symbol = 0;
  int flag_atoi = str_atoi(token, o_str, &power, 10, &n_symbol);
  if (flag_atoi != 0)
    number *= pow(10, power);
  else
    (*o_str) -= (n_symbol - 1);
  return number;
}

void write_var_f(va_list valist, format_tok *token, long double res,
                 int flag_atoi) {
  if (token->len == '1') {
    float *u = va_arg(valist, float *);
    if (flag_atoi == 1) *u = (float)res;
  } else if (token->len == 'l') {
    double *u = va_arg(valist, double *);
    if (flag_atoi == 1) *u = (double)res;
  } else if (token->len == 'L') {
    long double *u = va_arg(valist, long double *);
    if (flag_atoi == 1) *u = (long double)res;
  }
}

void write_persent(char **o_str) {
  if (**o_str == '%') {
    (*o_str)++;
  }
}

int str_atoi(format_tok *token, char **o_str, long int *res, int base,
             int *n_symbol) {
  int multi_sign = 0;
  int number = 0;
  int flag = 1;
  int sign = find_sign(token, o_str, &multi_sign, n_symbol);
  int base_valid = 1;

  while (**o_str >= '0' && **o_str <= '9' && token->width != 0 && base_valid) {
    if (base == 8 && (**o_str == '8' || **o_str == '9')) {
      base_valid = 0;
      number++;
    } else {
      *res = *res * 10 + (**o_str - '0');
      (*o_str)++;
      number++;
      if (token->width > -1) token->width--;
    }
    (*n_symbol)++;
  }
  *res *= sign;
  if (multi_sign > 1 || number == 0) flag = 0;
  return flag;
}

int find_sign(format_tok *token, char **o_str, int *multi_sign, int *n_symbol) {
  int sign = 1;
  while (**o_str == ' ' || **o_str == '-' || **o_str == '+') {
    if (**o_str == '-') {
      sign = -1;
      (*multi_sign)++;
      if (token->width > -1) token->width--;
    } else if (**o_str == '+') {
      if (token->width > -1) token->width--;
      (*multi_sign)++;
    }
    (*o_str)++;
    (*n_symbol)++;
  }
  return sign;
}