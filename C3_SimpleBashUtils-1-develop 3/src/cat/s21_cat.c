#include "s21_cat.h"

int main(int argc, char* argv[]) {
  opt options = {0};
  getoptLongParcer(argc, argv, &options);
  myReader(argc, argv, options);

  return 0;
}
