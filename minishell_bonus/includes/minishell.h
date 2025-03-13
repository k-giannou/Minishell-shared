/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:03:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/13 18:39:13 by locagnio         ###   ########.fr       */
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
# define BROWN	"\033[38;5;94m"
# define ORANGE "\033[38;5;214m"

# define DBL_Q '"'
# define SGL_Q '\''

# define INT64_Max "9223372036854775807"
# define INT64_Min "-9223372036854775808"

# define HOSTNAME "/etc/hostname"

extern sig_atomic_t	g_signal;

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
	char	*final;
	char	*hostname;
}	t_user;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
} t_env,	t_cell;

typedef struct s_pipes
{
	int		i;
	pid_t	*pids;
	int		**pipes;
	int		nb_pipes;
}	t_pipes;

typedef struct s_prior
{
    int	and;
	int	or;
	int	pipes;
	int	parenthesis;
}	t_prior;

typedef struct s_minishell
{
	int			fd;
	t_redirs	r;
	t_pipes		p;
	t_user		user;
	t_variables	vars;
	t_env		*env;
	t_prior		prior;
	bool		sgl_q;
	bool		dbl_q;
	char		**cmd_s;
	char		*cur_loc;
	char		**tokens;
	int			hist_lines;
	t_env		*env_export;
	char		**pipes_redirs;
}	t_minishell;

void	sig_init(void);
t_env	*ft_envdup(t_env *src);
int		check_quotes(char *str);
t_env	*create_cell(char *data);
void	ft_env_sort(t_env **begin_list);
int		rest_letters_of_name(char *str);
int		is_symbols(char **raw, int i);
void	ft_get_env(t_env **env, char *env_var);
t_env	*add_at(t_env *env, char *data, int pos);
char	*replace_var(t_minishell *mini, char *str);
void	valid_quotes(char c, bool *sgl_q, bool *dbl_q);
void	optimised_line(char *line, t_minishell **mini);
int		just_export_or_unset(char **vars, char *command);
char	*ft_strjoinm(char *s1, char *s2, int tab_to_free);
char	*replace_by_tilde(t_env *env, char *str, int free_str);
char	*ft_substr_with_quotes(char *line, t_minishell *mini, int len);

//print
void	welcome(void);
void	print_list(t_env *L);
void	ft_print_dlb_tabs(char **tab, char *arg);
void	print_pipes_redirs(char **split, int nb_words);
void	ft_print_export(t_env *v, bool sign, bool inside);

//frees
void	ft_list_clear(t_env *begin_list);
void	free_pipes(int **pipes, int nb_pipes);
void	free_all(t_minishell *mini, char *str);
void	free_pipes_redirs(char **str, int nb_words);


//pipes
char	*get_first_arg(char *av);
char	**splited_env(t_env *env);
int		get_file(char *av, int i);
char	*get_cmd(char **av, int i);
int		isredir_pipex(char *tokens);
void	set_symbols(t_minishell **mini);
char	*find_path(char *cmd, char **env);
void	read_stdin(int *fd, char *limiter);
void	create_pipes(t_pipes *pipes_struct);
void	pipex(t_minishell *mini, char **env);
void	execute(char **av, char **env, t_minishell *mini);
char	**get_redir_split(t_minishell *mini, int cur_cmd);
void	close_and_redirect_pipes(t_pipes *pipes_struct, int current_pipe);
void	close_curr_pipe(t_pipes *pipes_struct, int current_pipe, char **cmd_s);

//buildins
void	pwd(void);
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
int		redir(t_minishell *mini, char **env, char **tokens, char **pipes_redirs);
int		valid_filename(char **tab, char **ntab);
int		syntax_error_redir(char **tab, char **ntab);
void	find_tab(int *y, char **tab, char **tokens);
int		handle_files(char **tokens, char **pipes_redirs, t_redirs *r, int make_dup);
void	exec_buildin(char **tab, t_minishell *mini, int free);
void	join_command_free_tab(char **tab, char **tokens);
int		handle_heredoc (char **tokens, char **pipes_redirs);
char	**find_eofs(int *sum, char **tokens, char **pipes_redirs);
void	copy_eofs(int *sum, char **eofs, char **tokens, char **pipes_redirs);
int		heredoc (char **tokens, char **pipes_redirs);
void	free_strs(char **str1, char **str2, char **str3);
int		hd_filename(char **tokens, char ** pipes_redirs);
void	correct_null_tabs(int size_tokens, char **tokens, char **pipes_redirs);
int		syntax_error_before_hd(char **tokens, char **pipes_redirs);
int		error_in_heredoc(char **tokens, char **pipes_redirs, bool *error);
void	write_in_heredoc(int *first, int fd, char *line, char **eofs);
int		init_r(t_redirs *r, char **tokens);
void	restore_and_free(char **tab1, char *path, t_redirs *r);

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
