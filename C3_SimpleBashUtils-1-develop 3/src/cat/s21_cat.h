#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;

} opt;

typedef struct flags {
  int str_count;
  int empty_count;
  int current;
  int isSecondEmpty;

  int isCounter;
  int isPutchar;
  int isEnter;
  int isDollar;
  int isTab;

} flag;

void getoptLongParcer(int argc, char* argv[], opt* options);
void myReader(int argc, char* argv[], opt options);

void numbersFlagsN(flag* flags);
void numbersFlagsB(flag* flags);
void deliteEmptyStringsS(flag* flags);
void printDollarsAtEndE(opt options, flag* flags);
void printer(opt options, flag* flags, int v1, int v2);

#endif