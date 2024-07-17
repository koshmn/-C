#include "s21_grep.h"

void push_list(list **head, char *data) {
  list *tmp = (list *)malloc(sizeof(list) * 1);
  tmp->data = data;
  tmp->next = NULL;
  if ((*head) == NULL) {
    (*head) = tmp;
  } else {
    list *tmp2 = (*head);
    while (tmp2->next) {
      tmp2 = tmp2->next;
    }
    tmp2->next = tmp;
  }
}

void delete_list(list *head) {
  list *tmp = head;
  list *tmp2 = head;
  while (tmp->next != NULL) {
    tmp2 = tmp->next;
    free(tmp->data);
    free(tmp);
    tmp = tmp2;
  }
  free(tmp2->data);
  free(tmp2);
}

void init_inform(info *inf) {
  inf->i = 0;
  inf->v = 0;
  inf->c = 0;
  inf->n = 0;
  inf->l = 0;
  inf->h = 0;
  inf->s = 0;
  inf->files_counter = 0;
  inf->sample = NULL;
  inf->file = NULL;
}

void delete_inform(info *inf) {
  if (inf->file != NULL) {
    delete_list(inf->file);
  }
  if (inf->sample) {
    free(inf->sample);
  }
  free(inf);
}

void sample_maker(info *inf, char *s, char ch) {
  int old_sample_len = 0;
  int new_sample_len = 0;
  if (inf->sample) {
    old_sample_len = strlen(inf->sample);
  }
  new_sample_len = old_sample_len + strlen(s) + 2;
  char *new_sample = (char *)malloc(sizeof(char) * new_sample_len);
  for (int i = 0; i < old_sample_len; i++) {
    new_sample[i] = inf->sample[i];
  }
  if (old_sample_len != 0) {
    new_sample[old_sample_len] = ch;
  }
  int j = 0;
  int k = 0;
  if (old_sample_len == 0) {
    k = 0;
  } else {
    k = old_sample_len + 1;
  }
  for (int i = k; i < new_sample_len - 1; i++) {
    new_sample[i] = s[j];
    j++;
  }
  new_sample[new_sample_len - 1] = '\0';
  free(inf->sample);
  inf->sample = new_sample;
}  // эта функция к текущему шаблону добавляет | и новый паттерн для поиска в
   // флаге f или e

int file_parser(char *s, info *inf) {
  FILE *file = fopen(s, "r");
  int pattern_len = 0;
  size_t len = 0;
  int flag = 1;
  char *pattern = NULL;
  if (!file) {
    flag = 0;
  } else {
    while (getline(&pattern, &len, file) != -1) {
      pattern_len = strlen(pattern);
      if ((pattern[pattern_len - 1] == '\n') && (pattern_len != 1)) {
        pattern[pattern_len - 1] = '\0';
      }
      sample_maker(inf, pattern, '|');
    }
    free(pattern);
    fclose(file);
  }
  return flag;
}  // эта функция проверяет, является ли текущий аргумент файлом, парсит файл
   // для флага f и добавляет паттерны из него в шаблон для поиска

int flag_checker(info *inf, char *s, int flag) {
  int i = 0;
  while (s[i]) {
    if (s[i] == 'i')
      inf->i = 1;
    else if (s[i] == 'n')
      inf->n = 1;
    else if (s[i] == 'v')
      inf->v = 1;
    else if (s[i] == 'l')
      inf->l = 1;
    else if (s[i] == 'h')
      inf->h = 1;
    else if (s[i] == 'c')
      inf->c = 1;
    else if (s[i] == 's')
      inf->s = 1;
    else if (s[i] == 'f') {
      if (s[i + 1]) {
        if (!file_parser(&s[i + 1], inf)) {
          flag = -1;
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  &s[i + 1]);
          break;
        }
        flag = 3;
        break;
      } else {
        flag = 2;
      }
    } else if (s[i] == 'e') {
      if (s[i + 1]) {
        sample_maker(inf, &s[i + 1], '|');
        flag = 3;
        break;
      } else {
        flag = 1;
      }
    }
    i++;
  }
  return flag;
}  // возвращает -1, если не файл или флаг

int e_f_checker(char *argv[], int argc) {
  int flag = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      int j = 0;
      while (argv[i][j]) {
        if ((argv[i][j] == 'f') || (argv[i][j] == 'e')) {
          flag = 1;
        }
        j++;
      }
    }
  }
  return flag;
}  // возвращает 1, если есть флаг e или f

int arg_parser(int argc, char *argv[], info *inf) {
  int flag = 0;
  int flag_e_f = e_f_checker(argv, argc);
  int ret = 0;
  for (int i = 1; i < argc; i++) {
    if ((flag == 0 || flag == 3) && argv[i][0] == '-') {
      flag = flag_checker(inf, argv[i], flag);
      if (flag == -1) {
        ret = 1;
        break;
      }
    } else if (flag == 1) {
      sample_maker(inf, argv[i], '|');
      flag = 3;
    } else if (flag == 2) {
      if (!file_parser(argv[i], inf)) {
        fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[i]);
        ret = 0;
        break;
      }
      flag = 3;
    } else if ((flag_e_f == 0) && (flag == 0)) {
      sample_maker(inf, argv[i], '|');
      flag = 3;
    } else {
      char *file = (char *)malloc(sizeof(char) * (strlen(argv[i]) + 1));
      sprintf(file, "%s", argv[i]);
      push_list(&inf->file, file);
      inf->files_counter++;
    }
  }
  return ret;
}  // 0, если неправильный файл или флаг

void result_printer(info *inf) {
  if (inf->file == NULL) {
    fprintf(stderr, "s21_grep: No files\n");
  } else {
    char *line = NULL;
    size_t len = 0;
    list *cur_file = inf->file;
    regex_t regexp;
    if (regcomp(&regexp, inf->sample,
                inf->i ? REG_ICASE | REG_EXTENDED | REG_NEWLINE
                       : REG_EXTENDED | REG_NEWLINE)) {
      fprintf(stderr, "s21_grep: Incorrect regular expression\n");
    }
    int match = 0;
    while (cur_file) {
      int line_counter = 1;
      int match_line_counter = 0;
      FILE *file;
      file = fopen(cur_file->data, "r");
      if (file == NULL) {
        if (inf->s == 0) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  cur_file->data);
        }
      } else {
        while (getline(&line, &len, file) != -1) {
          match = regexec(&regexp, line, 0, 0, 0);
          if (inf->v) {
            if (match) {
              match = 0;
            } else {
              match = 1;
            }
          }
          if (!match) {
            match_line_counter++;
          }
          if (!match && !inf->l && !inf->c) {
            if (inf->files_counter > 1 && !inf->h) {
              printf("%s:", cur_file->data);
            }
            if (inf->n) {
              printf("%d:", line_counter);
            }
            printf("%s", line);
            if (line[strlen(line) - 1] != '\n') {
              printf("\n");
            }
          }
          line_counter++;
        }
        if (inf->c) {
          if ((inf->files_counter > 1) && (!inf->h)) {
            printf("%s:", cur_file->data);
          }
          if (inf->l && match_line_counter) {
            match_line_counter = 1;
          }
          printf("%d\n", match_line_counter);
        }
        if (inf->l && (match_line_counter > 0)) {
          printf("%s\n", cur_file->data);
        }
        fclose(file);
      }
      cur_file = cur_file->next;
    }
    regfree(&regexp);
    free(line);
  }
}
