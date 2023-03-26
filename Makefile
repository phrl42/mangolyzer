SRC_DIR := src
OBJ_DIR = bin/
INC_DIR = include/

NAME = game
SRCS := $(shell ls src/ -R |grep ".cpp") 
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

CC = clang++
CFLAGS = -Wall -Wextra -pedantic -g -Iinclude/banana -Iinclude/game -Iinclude
LFLAGS = -lSDL2 -lm -lGL 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJ_DIR)*
	rm -f $(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean run
