CC=gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

OS = $(shell uname)

ifeq ($(OS), Linux)
	LINUX_LIBS=-D_GNU_SOURCE
endif

.PHONY: all clean test s21_grep

all: build test clean

build: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -g -lpcre $(LINUX_LIBS) -o s21_grep

test: buld s21_grep
	python3 *.py

lint:
	clang-format -n -Werror *.[ch]

leaks: build
	valgrind --leak-check=full  --show-leak-kinds=all --track-origins=yes ./s21_grep
clean:
	- rm s21_grep
	- rm -rf *.o
	- rm 0_*.*