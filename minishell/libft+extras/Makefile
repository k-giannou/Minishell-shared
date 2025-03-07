MAKEFLAGS += -s

CC = cc
FLAGS = -Wall -Wextra -Werror

SRCS_DIR = ../
OBJ_DIR = ../obj

NAME = libft.a

SRCS = $(shell find $(SRCS_DIR) -type f -name '*.c')

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)

CYAN	= "\033[36m"
GREEN	= "\033[32m"
RESET	= "\033[0m"

all : message $(NAME)

message:
	@echo $(CYAN)"Compilation de la libft..."$(RESET)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	@echo $(GREEN)"libft crée !"$(RESET)

$(OBJ_DIR)/%.o : $(SRCS_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I ../includes -c $< -o $@

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all
