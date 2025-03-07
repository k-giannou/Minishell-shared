MAKEFLAGS += -s  # Active le mode silencieux globalement

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
RED				= "\033[31m"
GREEN			= "\033[32m"
RESET			= "\033[0m"

all: $(NAME)

# Création de l'exécutable
$(NAME): $(LIBFT) $(SRC_O)
	@echo $(CYAN)"Compilation de minishell..."$(RESET)
	@$(CC) $(FLAGS) $(SRC_O) -L libs -lfprintf -lft -I $(HDRS) -o $(NAME) -lreadline
	@echo $(GREEN)"Exécutable $(NAME) créé !"$(RESET)

# Règle pour compiler la libft (appelle le Makefile dans libft+extras)
$(LIBFT):
	@mkdir -p $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/libft.a libs/

# Compilation des fichiers sources en objets dans le répertoire obj/
$(OBJ_DIR)/%.o: $(SRCS_DIR)%.c $(HDRS)/*.h
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@


# Nettoyage des objets
clean:
	@echo $(CYAN)"Suppression des fichiers objets..."$(RESET)
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Nettoyage complet
fclean: clean
	@echo $(CYAN)"Suppression de l'exécutable..."$(RESET)
	@$(RM) $(NAME)
	@echo $(CYAN)"Suppression de la libft..."$(RESET)
	@$(RM) libs/libft.a

# Récompilation complète depuis zéro
re: fclean all

# Sécurité des règles
.PHONY: all clean fclean re