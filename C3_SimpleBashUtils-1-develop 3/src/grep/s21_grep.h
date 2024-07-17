#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct lst {
  char *data;
  struct lst *next;
} list;

typedef struct inform {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int files_counter;
  list *file;
  char *sample;
} info;

void init_inform(info *inf);
void delete_list(list *head);
void delete_inform(info *inf);
void sample_maker(info *inf, char *s, char ch);
int file_parser(char *s, info *inf);
void push_list(list **head, char *data);
int flag_checker(info *inf, char *s, int state);
int e_f_checker(char *argv[], int argc);
int arg_parser(int argc, char *argv[], info *inf);
void result_printer(info *inf);

#endif  // SRC_GREP_S21_GREP_H_
