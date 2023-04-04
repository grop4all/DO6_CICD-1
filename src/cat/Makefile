CC=gcc

Flag:= -Wall -Werror -Werror -std=c11

SRC:=$(shell find *.[ch])

file:= s21_cats

all: build test clean

build:
	$(CC) $(Flag) $(SRC) -o $(file)

test: build
	s21_cat_tests.py

clean:	
	rm $(file)