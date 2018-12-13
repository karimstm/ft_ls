NAME = ft_ls

SRC = src
BIN = bin
INC = inc

SOURCE = $(wildcard $(SRC)/*.c)
OBJECT = $(patsubst %, $(BIN)/%, $(notdir $(SOURCE:.c=.o)))

CC = gcc
FLAGS = -Wall -Wextra -Werror
CPP_FLAGS = -I$(INC) -Ift_printf/inc
FTPRINTF = ft_printf/libftprintf.a

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME):$(OBJECT) $(FTPRINTF)
	@echo "$(RED)Linking...$(NC)"
	$(CC) $(OBJECT) $(FTPRINTF) -o $(NAME)
	@echo "$(GREEN)Finished...$(NC)"

$(FTPRINTF):
	@make -C ft_printf

$(BIN)/%.o : $(SRC)/%.c
	@echo "$(BLUE)Compiling...$(NC)"
	$(CC) $(FLAGS) $(CFLAGS) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECT)
	make -C ft_printf clean

fclean:clean
	rm -rf $(NAME)
	make -C ft_printf fclean

re : fclean all

.PHONY: all clean fclean re help

help :
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"
