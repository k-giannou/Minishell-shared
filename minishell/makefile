MAKEFLAGS += -s  # Active le mode silencieux globalement

# Définition des variables
CC				= cc
FLAGS			= -Wall -Wextra -Werror -lreadline -g
HDRS			= includes
SRCS			=  srcs/minishell.c srcs/print.c srcs/exec.c srcs/free.c srcs/utils/utils.c\
				   srcs/utils/utils2.c srcs/utils/ft_split.c srcs/buildins/pwd.c\
				   srcs/buildins/env.c srcs/buildins/echo.c srcs/optimized_argument.c\
				   srcs/utils/repl.c srcs/utils/ft_list_sort.c\
				   \
				   srcs/gnl/get_next_line_bonus.c srcs/gnl/get_next_line_utils_bonus.c
SRC_O			= $(SRCS:srcs/.c=.o)
PHILO_NAME		= minishell
RM				= rm -f
CYAN			= "\033[36m"
RED				= "\033[31m"
GREEN			= "\033[32m"
RESET			= "\033[0m"

# Règle par défaut : création de l'exécutable
all: $(PHILO_NAME)

# Création de l'exécutable
$(PHILO_NAME): $(SRC_O)
	@echo $(CYAN)"Création de l'exécutable $(PHILO_NAME)..."$(RESET)
	@$(CC) $(FLAGS) $(SRC_O) -L lib -lfprintf -I $(HDRS) -o $(PHILO_NAME)
	@echo $(GREEN)"Exécutable $(PHILO_NAME) créé !"$(RESET)

# Compilation des fichiers sources en objets
# On compiles les fichiers .c dans srcs/ en .o dans le répertoire racine
%.o: philo\ /%.c $(HDRS)/*.h
	@echo $(CYAN)"Compilation de $<..."$(RESET)
	@$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@

# Nettoyage des objets
clean:
	@echo $(CYAN)"Suppression des fichiers objets..."$(RESET)
	@$(RM) *.o */*.o */*/*.o

# Nettoyage complet
fclean: clean
	@echo $(CYAN)"Suppression de l'exécutable..."$(RESET)
	@$(RM) $(PHILO_NAME)

# Récompilation depuis zéro
re: fclean all

# Sécurité des règles
.PHONY: all clean fclean re
