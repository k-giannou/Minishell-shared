/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:03:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/11 20:50:46 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_fprintf.h"
# include "get_next_line_bonus.h"
# include <sys/stat.h>
# include <wait.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>

# define RESET		"\033[0m"   //Réinitialisation
# define RED		"\033[31m"   //Couleur rouge
# define GREEN       "\033[32m"  // Couleur verte
# define YELLOW      "\033[33m"  // Couleur jaune
# define BLUE        "\033[34m"  // Couleur bleue
# define MAGENTA     "\033[35m"  // Couleur magenta
# define CYAN        "\033[36m"  // Couleur cyan
# define BOLD		"\033[1m"  // Texte en gras
# define ITALIC      "\033[3m"  // Texte en italique
# define UNDERLINE	"\033[4m"  // Texte souligné

#define DBL_Q '"'
#define SGL_Q '\''
#define HISTORY ".history.txt"

extern volatile sig_atomic_t g_signal;

typedef struct s_env
{
	char	*data;
	struct s_env	*next;	
} t_env, t_cell;

typedef struct s_variables
{
	char	line[70000];//we check the str and we copy char by char in like, except it needs replace
	char	to_search[70000];
    int	i;
	int	k;
	int	t;
	bool dbl_quote;
	int	quote_sum;
} t_variables ;

typedef struct s_minishell
{
	bool	sgl_q;
	bool	dbl_q;
	int		fd;
	int		hist_lines;
	char	*current_location;
	t_env	*env;
	t_env	*env_export;
	t_variables vars;
} t_minishell;


void	error(void);
void	welcome(void);
void	sig_init(void);
char	*ft_itoa(int n);
int		ft_isalnum(char c);
void	print_list(t_env *L);
t_env	*ft_envdup(t_env *src);
t_env	*create_cell(char *data);
char	*ft_strdup(const char *src);
void	ft_print_dlb_tabs(char **tab);
void	ft_putstr_fd(char *s, int fd);
void	ft_env_sort(t_env **begin_list);
char	**ft_split(char *str, char *charset);
t_env	*add_at(t_env *L, char *data, int pos);
void	ft_exit(t_minishell *mini, char **line);
char	*ft_readline(char *str, t_minishell *mini);
char	*replace_var(t_minishell *mini, char *str);
char	*ft_strjoinm(char const *s1, char const *s2);
void	valid_quotes(char c, bool *sgl_q, bool *dbl_q);
char	**optimised_line(char *line, t_minishell *mini);
char	*ft_remove_from_string(char *str, char *to_delete);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//frees
void	ft_list_clear(t_env *begin_list);
void	free_all(t_minishell *mini, char **str);

//buildins
void	pwd(t_env *env);
void	ft_env(t_env *env);
void	echo(char **line);
void	cd(char *chemin, t_minishell **mini);
void	exec_cmd(char **line, t_minishell *mini);

char    *replace_var(t_minishell *mini, char *str);
int	ft_charset(int c);

# endif
