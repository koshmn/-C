#ifndef S21_STRING_H
#define S21_STRING_H

#include <limits.h>
#include <locale.h>  // p
#include <math.h>    // s&p
#include <stdarg.h>  // s&p
#include <stddef.h>  // p
#include <stdint.h>  // p
#include <stdio.h>
#include <stdlib.h>  // p
#include <wchar.h>   // s

#define s21_size_t unsigned long long
#define s21_NULL (void *)0
#define BUFF 1024       // sprintf
#define BUFF_SIZE 1024  // sprintf
// typedef long unsigned s21_size_t; pomyanem

typedef struct {  // sprintf
  int minus;
  int plus;
  int space;
  int precision;
  int is_precision;
  int width;
  char length;
  char specificator;
} flags;

typedef struct {  // sscanf
  short flag;  // short, оно же short int, оно же целое число 2 байт //(-1)
  char specifiers;  //'0'
  int width;        // -1
  char len;         // 1
} format_tok;

s21_size_t s21_strlen(const char *str);  // mayraqor
s21_size_t s21_strcspn(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);        // mayraqor
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);  // lanstert
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strerror(int errnum);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strtok(char *str, const char *delim);  // lanstert

void *s21_to_upper(const char *str);  // abahwarr
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);  // abahwarr

void double_to_string(long double number, char *result, flags f);  // kenchsoc
void obnull(char *buffer);

int is_digit(char c);
int s21_sprintf(char *str, const char *format, ...);
const char *get_flags(const char *format, flags *f);

const char *get_width(const char *format, flags *f, va_list va);
const char *get_precision(const char *format, flags *f, va_list va);
const char *get_length(const char *format, flags *f);

void num_to_string(int64_t val, char *ret, int base);
void unum_to_string(uint64_t val, char *ret, int base);
void format_precision(char *buffer, flags f);
int int_flags(char c);

void writing(flags f, char *buffer, va_list va);
void parse_uint(flags f, char *buffer, va_list va);
void parse_int(flags f, char *buffer, va_list va);

void parse_char(flags f, char *buffer, va_list va);
void format_wchar(flags f, char *buffer, wchar_t w_c);
void format_char(flags f, char *buffer, char c);
void parse_string(flags f, char *buffer, va_list va);
void format_string(flags f, char *buffer, char *str);
char *s21_strcpy(char *s, const char *t);
void format_wide_string(flags f, char *buffer, wchar_t *wstr);  // kenchsoc

int s21_sscanf(const char *str, const char *format,
               ...);  // - считывает форматированный ввод из строки. gatesbri
int format_parse(format_tok *token, char **o_format);
int format_parse_width(char **o_format, format_tok *token);
void format_parse_length(char **o_format, format_tok *token);
void format_parse_specifier(char **o_format, format_tok *token);
int format_valid(format_tok *token);

int str_write(va_list valist, format_tok *token, char **o_str, char *start,
              int *valid);
int write_c(va_list valist, format_tok *token, char **o_str);
int write_d(va_list valist, format_tok *token, char **o_str, int *valid);
int write_i(va_list valist, format_tok *token, char **o_str);
int write_o(va_list valist, format_tok *token, char **o_str, int sign);
int write_s(va_list valist, format_tok *token, char **o_str);
int write_u(va_list valist, format_tok *token, char **o_str, int *valid);
int write_x(va_list valist, format_tok *token, char **o_str, int sign);
int write_p(va_list valist, format_tok *token, char **o_str);
int write_f(va_list valist, format_tok *token, char **o_str);
void write_persent(char **o_str);

int find_sign(format_tok *token, char **o_str, int *multi_sign, int *n_symbol);
void write_var_d(va_list valist, format_tok *token, long int res,
                 int flag_atoi);
void write_var_u(va_list valist, format_tok *token, long int res,
                 int flag_atoi);
void write_var_f(va_list valist, format_tok *token, long double res,
                 int flag_atoi);
void oct_to_dec(long int number, long int *decimal);
long double scan_e(format_tok *token, char **o_str, long double number);
int str_atoi(format_tok *token, char **o_str, long int *res, int base,
             int *n_symbol);
int str_16_atoi(format_tok *token, char **o_str, long int *res);
long int to_digit(char c);  // gatesbri

#endif
