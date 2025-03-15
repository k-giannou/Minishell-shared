MAKEFLAGS += -s

CC				= cc
FLAGS			= -Wall -Wextra -Werror -g
HDRS			= includes
LIBFT_DIR		= libft+extras
LIBFT			= $(LIBFT_DIR)/libft.a
SRCS_DIR		= ./
OBJ_DIR			= obj

SRCS			= $(shell find $(SRCS_DIR)/minishell_srcs -type f -name '*.c')

SRC_O			= $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)

NAME			= minishell
RM				= rm -f
CYAN			= "\033[36m"
GREEN			= "\033[32m"
RESET			= "\033[0m"

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_O)
	@echo $(CYAN)"Compilation de minishell..."$(RESET)
	@$(CC) $(FLAGS) $(SRC_O) -L libs -lfprintf -lft -I $(HDRS) -o $(NAME) -lreadline
	@echo $(GREEN)"Exécutable $(NAME) créé !"$(RESET)

$(LIBFT):
	@mkdir -p $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/libft.a libs/

$(OBJ_DIR)/%.o: $(SRCS_DIR)%.c $(HDRS)/*.h
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@


clean:
	@echo $(CYAN)"Suppression des fichiers objets..."$(RESET)
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CYAN)"Suppression de l'exécutable..."$(RESET)
	@$(RM) $(NAME)
	@echo $(CYAN)"Suppression de la libft..."$(RESET)
	@$(RM) libs/libft.a

re: fclean all

.PHONY: all clean fclean re