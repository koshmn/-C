CC=gcc
FLAGS= -std=c11 -Wall -Wextra -Werror 
PATH_build= ./
CAT = ./
GREP = ./grep/


all: s21_cat

s21_cat:
	$(CC) $(FLAGS) $(CAT)s21_cat.c  $(CAT)cat_func.c -o $(PATH_build)s21_cat

# s21_grep:
# 	$(CC) $(FLAGS) $(GREP)s21_grep.c $(GREP)grep_func.c -o $(PATH_build)grep/s21_grep 

clean:
	rm -rf $(CAT)*.o $(CAT)*.exe $(GREP)*.o $(GREP)*.exe $(PATH_build)cat/s21_cat $(PATH_build)grep/s21_grep

rebuild: clean all
# mingw32-make s21_grep -lregex