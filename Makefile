SRC_DIR := src
OBJ_DIR = bin/
INC_DIR = include/

NAME = game
SRCS := $(shell ls src/ -R |grep ".cpp") 
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

CC = clang++
CFLAGS = -Wall -Wextra -pedantic -g -Iinclude/banana -Iinclude/game -Iinclude/banana/utils -Iinclude
LFLAGS = -lSDL2 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
CPPFLAGS = -DMACRO_SDL2 -DMACRO_OPENGL

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJ_DIR)*
	rm -f $(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean run
