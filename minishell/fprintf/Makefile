MAKEFLAGS += -s

CC = cc

FLAGS = -Wall -Wextra -Werror -w -g

SRCS_DIR = ../
OBJ_DIR = ../obj

NAME = libfprintf.a

LIBFT = ft_fprintf.h

SRCS = $(shell find $(SRCS_DIR) -type f -name '*.c')

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)

CYAN	= "\033[36m"
GREEN	= "\033[32m"
RESET	= "\033[0m"

all: message ${NAME}

message:
	@echo $(CYAN)"Compilation de fprintf..."$(RESET)

${NAME}: ${OBJS}
	ar -rcs $(NAME) $(OBJS)
	@echo $(GREEN)"libfprintf crée !"$(RESET)

$(OBJ_DIR)/%.o : $(SRCS_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I ../includes -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

bonus: $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
