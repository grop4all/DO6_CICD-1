CC=gcc

Flag:= -Wall -Werror -Werror -std=c11

SRC:=$(shell find *.[ch])

file:= s21_cat

all: build test clean

build:
	$(CC) $(Flag) $(SRC) -o $(file)

test: build
	python3 s21_cat_tests.py

lint:
	clang-format -n -Werror *.[ch]

leaks: build
	valgrind --leak-check=full  --show-leak-kinds=all --track-origins=yes ./$(file)


clean:	
	rm $(file)