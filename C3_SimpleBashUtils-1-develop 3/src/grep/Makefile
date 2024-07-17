CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
all: s21_grep
s21_grep: s21_grep.o s21_main.o
	$(CC) -Wall -Wextra -Werror s21_grep.o s21_main.o -o s21_grep
s21_main.o: s21_main.c
	$(CC) $(CFLAGS) s21_main.c
s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c
test_style:
	cp ../../materials/linters/.clang-format ..
	cd .. && exec clang-format -i -style=Google grep/*.c
	cd .. && exec clang-format -i -style=Google grep/*.h
clean: 
	rm -rf *.o s21_grep
rebuild:
	$(MAKE) clean
	$(MAKE) all