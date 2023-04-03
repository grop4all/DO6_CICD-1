CC=gcc

Flag:= -Wall -Werror -Werror -std=c11

SRC:=$(shell find *.[ch])


all: build

build:
	$(CC) $(Flag) $(SRC) -o $(file)

clean:
	rm $(file)