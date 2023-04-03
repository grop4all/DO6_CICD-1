CC=gcc

Flag:= -Wall -Werror -Werror -std=c11

SRC:=$(shell find *.[ch])
file = s21_cat

all: s21_cat

$(file):
	$(CC) $(Flag) $(SRC) -o $(file)

clean:
	rm $(file)