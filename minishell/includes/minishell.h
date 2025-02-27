/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:03:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/27 16:07:25 by locagnio         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <wait.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
# include <stdint.h>

# include "libft_extras.h"
# include "ft_fprintf.h"
# include "get_next_line_bonus.h"

# define RESET		"\033[0m"   //Réinitialisation
# define BOLD		"\033[1m"  // Texte en gras
# define ITALIC      "\033[3m"  // Texte en italique
# define UNDERLINE	"\033[4m"  // Texte souligné
# define RED		"\033[31m"   //Couleur rouge
# define GREEN       "\033[32m"  // Couleur verte
# define YELLOW      "\033[33m"  // Couleur jaune
# define BLUE        "\033[34m"  // Couleur bleue
# define MAGENTA     "\033[35m"  // Couleur magenta
# define CYAN        "\033[36m"  // Couleur cyan
# define BRIGHT_GREEN  "\033[92m"  // Couleur verte claire

# define DBL_Q '"'
# define SGL_Q '\''

# define INT64_Max "9223372036854775807"
# define INT64_Min "-9223372036854775808"

# define HOSTNAME "/etc/hostname"

extern volatile sig_atomic_t	g_signal;

typedef struct s_variables
{
	char	line[70000];
	char	to_search[70000];
	int		i;
	int		k;
	int		t;
	bool	dbl_quote;
	int		quote_sum;
}	t_variables;

typedef enum
{
    REDIR_NONE,// -
    REDIR_OUT, // >
    REDIR_APPEND,// >>
	REDIR_IN,// <
	REDIR_IN_OUT,//<>
	HEREDOC// <<
}	t_type;

typedef struct s_redirs
{
	int	saved_in;
	int	saved_out;
	t_type	type;
	char	**tab;
	int	fd;
	int	y;
}	t_redirs;

typedef struct s_user
{
	char	*name;
	char	*hostname;
	char	*final;
}	t_user;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
} t_env,	t_cell;

typedef struct s_minishell
{
	bool		sgl_q;
	bool		dbl_q;
	int			fd;
	int			hist_lines;
	char		*cur_loc;
	char		**tokens;
	char		**pipes_redirs;
	t_env		*env;
	t_env		*env_export;
	t_user		user;
	t_variables	vars;
	t_redirs	r;
}	t_minishell;

void	sig_init(void);
t_env	*ft_envdup(t_env *src);
int		check_quotes(char *str);
t_env	*create_cell(char *data);
void	ft_env_sort(t_env **begin_list);
int		rest_letters_of_name(char *str);
t_env	*add_at(t_env *L, char *data, int pos);
void	ft_get_env(t_env **env, char *env_var);
char	*replace_by_tilde(t_env *env, char *str);
char	*replace_var(t_minishell *mini, char *str);
void	valid_quotes(char c, bool *sgl_q, bool *dbl_q);
void	optimised_line(char *line, t_minishell **mini);
int		just_export_or_unset(char **vars, char *command);
char	*ft_strjoinm(char *s1, char *s2, int tab_to_free);
void	is_redir_or_pipes(char **raw, bool sgl_q, bool dbl_q);
char	*ft_substr_with_quotes(char *line, t_minishell *mini, int len);

//print
void	error(void);
void	welcome(void);
void	print_list(t_env *L);
void	ft_print_dlb_tabs(char **tab, char *arg);
void	print_pipes_redirs(char **split, int nb_words);
void	ft_print_export(t_env *v, bool sign, bool inside);

//frees
void	ft_list_clear(t_env *begin_list);
void	free_all(t_minishell *mini, char *str);

//pipes
int		pipe_count(char **line);
void	here_doc(char *limiter);
char	**splited_env(t_env *env);
int		get_file(char *av, int i);
char	*get_cmd(char **av, int i);
int		isredir_pipex(char *tokens);
char	*find_path(char *cmd, char **env);
void	read_stdin(int *fd, char *limiter);
void	pipex(t_minishell *mini, char **env);
char	**get_redir_split(t_minishell *mini, int *j);
void	execute(char *av, char **env, t_minishell *mini);

//buildins
void	pwd(t_env *env);
void	echo(char **line);
void	ft_env(t_env *env);
void	ft_exit(t_minishell *mini);
void	exec_cmd(t_minishell *mini);
void	cd(char **chemin, t_minishell **mini);
void	unset(char **vars, t_minishell *mini);
void	export(char **vars, t_minishell *mini);

//redirs
void	restore_dup(t_redirs *r);
int		isredir(t_minishell *mini);
char	**copy_tokens(char **tokens);
int		is_buildin(char *tab, int to_free);
int		redir(t_minishell *mini, char **env);
int		valid_filename(char **tab, char **ntab);
int		syntax_error_redir(char **tab, char **ntab);
void	find_tab(int *y, char **tab, char **tokens);
int		last_file(int y, char **tab, char **tokens);
void	exec_buildin(char **tab, t_minishell *mini, int free);
void	join_command_free_tab(char **tab, char **tokens);

//utils
char	*hostname(void);
int		ft_charset(int c);
long	len_list(t_env *list);
char	*host_dup(char *name);
void	init_v(t_variables v);
void	init_user(t_minishell *mini);
int		first_letter_valid(char *str);
int		ft_strrchr(const char *s, int c);
char	*return_tab(int tab, int *new_i);
char	*ft_strsrch(const char *s, char *c);
void	change_bools(t_variables *v, char *str);
void	handle_single(t_variables *v, char *str);
void	remove_multiple_slashs(char *path, int i);
void	ft_list_add_back(t_env **lst, t_env *new);
char	*replace_var(t_minishell *mini, char *str);
void	if_pipes_or_redirs(char *line, int *i, int *count);
void	ft_substr_mini_2(char *line, t_minishell **mini, int *len);

#endif
