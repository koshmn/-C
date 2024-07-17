#include "s21_cat.h"

void getoptLongParcer(int argc, char* argv[], opt* options) {
  static struct option longOptions[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {NULL, 0, NULL, 0}};

  int opt;
  int index;

  while ((opt = getopt_long(argc, argv, "+benstvTE", longOptions, &index)) !=
         -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case '?':
        exit(EXIT_FAILURE);
        break;
      default:
        break;
    }
  }
}

void myReader(int argc, char* argv[], opt options) {
  flag flags = {0};
  flags.str_count = 1;
  flags.empty_count = 1;

  for (int i = optind; i < argc; i++) {
    FILE* myFile = fopen(argv[i], "r");
    if (myFile == NULL) {
      fprintf(stderr, "s21_cat ERROR: No such file or directory: %s\n",
              argv[i]);
      continue;
    }

    flags.isSecondEmpty = 1;

    while ((flags.current = fgetc(myFile)) != EOF) {
      flags.isCounter = 0;
      flags.isPutchar = 1;
      flags.isEnter = 0;
      flags.isDollar = 0;
      flags.isTab = 0;

      if (options.n && !options.b) {
        numbersFlagsN(&flags);
      }

      if (options.b) {
        numbersFlagsB(&flags);
      }

      if (options.s) {
        deliteEmptyStringsS(&flags);
      }

      if (options.e) {
        printDollarsAtEndE(options, &flags);
      }
      if (options.t) {
        if (flags.current == '\t') {
          flags.isTab = 1;
          flags.isPutchar = 0;
        }
      }

      int v1 = 0;
      int v2 = 0;
      if (options.v && (flags.current < 32 || flags.current == 127) &&
          flags.current != '\n' && flags.current != '\t') {
        v1 = 1;
        flags.isPutchar = 0;
      }
      if (options.v && (flags.current > 127)) {
        v2 = 1;
        flags.isPutchar = 0;
      }

      printer(options, &flags, v1, v2);
    }

    fclose(myFile);
  }
}

void numbersFlagsN(flag* flags) {
  if (flags->current == '\n') {
    flags->isEnter = 1;
    flags->isCounter = 1;
    flags->isPutchar = 0;
  }

  if (flags->str_count == 1) {
    printf("%6d\t", flags->str_count++);
  }
}

void numbersFlagsB(flag* flags) {
  if (flags->current == '\n') {
    flags->empty_count = 1;
    flags->isPutchar = 0;
    flags->isEnter = 1;
  } else {
    if (flags->empty_count) {
      flags->isCounter = 1;
      flags->empty_count = 0;
    }
    flags->isPutchar = 1;
  }
}

void deliteEmptyStringsS(flag* flags) {
  if (flags->current != '\n') {
    flags->isSecondEmpty = 0;
    flags->isPutchar = 1;
    flags->isEnter = 0;
  } else {
    if (flags->isSecondEmpty <= 1) {
      flags->isEnter = 1;
      flags->isSecondEmpty++;
      flags->isPutchar = 0;
    } else {
      flags->isPutchar = 0;
      flags->isEnter = 0;
      flags->isCounter = 0;
    }
  }
}

void printDollarsAtEndE(opt options, flag* flags) {
  if (flags->current == '\n' && !options.s) {
    flags->isDollar = 1;
    flags->isPutchar = 0;
    flags->isEnter = 1;
  } else if ((flags->current == '\n' && options.s)) {
    if (flags->isEnter == 0) {
      flags->isDollar = 0;
    } else {
      flags->isDollar = 1;
    }

  } else {
    flags->isPutchar = 1;
    flags->isEnter = 0;
    flags->isDollar = 0;
  }
}

void printer(opt options, flag* flags, int v1, int v2) {
  if (flags->isDollar) printf("$");
  if (flags->isEnter) printf("\n");
  if (flags->isCounter) printf("%6d\t", flags->str_count++);
  if (flags->isTab && !options.v) printf("^I");
  if (flags->isPutchar) putchar(flags->current);
  if (v1) printf("^%c", flags->current ^ 0b1000000);
  if (v2) printf("M-%c", flags->current ^ 0b10000000);
}