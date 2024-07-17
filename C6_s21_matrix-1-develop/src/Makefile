CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
TEST_FLAGS=-fsanitize=address -g
MAC_FLAGS=-lcheck -lm
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

VALGRIND_FLAGS = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LINUX_FLAGS=-lcheck -lsubunit -lrt -lpthread -lm

FILES=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o,$(FILES))
TEST_FILES=$(wildcard ./tests/s21_test.c)

MYLIB = s21_matrix.a

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
	OPEN=open
endif
ifeq ($(OS),Linux)
	OPEN=xdg-open
endif

all: gcov_report

.PHONY: all test memory_test s21_matrix.a gcov_report clean rebuild

s21_matrix.a: $(FILES)
	$(CC) -c $(FLAGS) $(FILES)
	ar rc $@ $(OBJ)
	ranlib $@
	rm -rf *.o

test: s21_matrix.a
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(TEST_FILES) $< -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(TEST_FILES) $< -o test $(LINUX_FLAGS)
endif
	./test

gcov_report: clean
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(LINUX_FLAGS)
endif
	./test
	rm *_test*
	lcov -t "s21_test" -o postreport.info --no-external -c -d .
	genhtml -o report postreport.info
	$(OPEN) report/index.html

style_check:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=Google *.c *.h tests/*.c
	clang-format -n -style=Google *.c *.h tests/*.c
	rm .clang-format

memory_check: s21_matrix.a
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) $< -o memory_test $(MAC_FLAGS)
	CK_FORK=no leaks --atExit -- ./memory_test
else
	$(CC) -g $(FLAGS) $(TEST_FILES) $< -o memory_test $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./memory_test
endif
	
clean_gcov:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf test
	rm -rf report
	rm -rf postreport.info

clean: clean_gcov
	rm -rf *.o
	rm -rf *.a
	rm -rf test
	rm -rf memory_test

rebuild:
	$(MAKE) clean
	$(MAKE) all