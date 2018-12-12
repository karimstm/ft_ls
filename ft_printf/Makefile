NAME = libftprintf.a 

SRC = src
BIN = bin
INC = inc

SOURCE = $(wildcard $(SRC)/*.c)
OBJECT = $(patsubst %, $(BIN)/%, $(notdir $(SOURCE:.c=.o)))

CC = gcc
FLAGS = -Wall -Wextra -Werror
CPP_FLAGS = -I$(INC)

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME):$(OBJECT)
	@echo "$(RED)Linking...$(NC)"
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)
	@echo "$(GREEN)Finished...$(NC)"

$(BIN)/%.o : $(SRC)/%.c
	@echo "$(BLUE)Compiling...$(NC)"
	$(CC) $(FLAGS) $(CFLAGS) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECT)

fclean:clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re help

help :
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"
