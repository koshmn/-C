#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int ret = 0;
  info *inf = (info *)malloc(sizeof(info));
  init_inform(inf);
  if (arg_parser(argc, argv, inf)) {
    ret = 1;
    delete_inform(inf);
  }
  if (ret == 0) {
    result_printer(inf);
    delete_inform(inf);
  }
  return ret;
}
