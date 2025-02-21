
NAME = program
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I/usr/local/include/SDL3
# LDFLAGS = -L/usr/local/lib -lSDL3
TARGET = SDL3_C_Test
SRC = 	src/main.c src/cellular.c
		

all: $(NAME)

$(NAME): $(SRC)
	gcc -o $(NAME) $(SRC) -I$(brew --prefix sdl3)/include -L$(brew --prefix sdl3)/lib -lSDL3

clean:
	rm -f $(NAME)

