/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/07 17:34:14 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_if_needed(char **env, t_minishell *mini)
{
	int		sig;
	char	**split;
	char	**redirs;

	sig = 0;
	split = NULL;
	redirs = NULL;
	if (mini->cmd_s_redirs[mini->p.i])
	{
		split = ft_splitdup(mini->cmd_s[mini->p.i]);
		redirs = get_redir_split(mini, mini->p.i);
		sig = redir(mini, env, split, redirs);
		free_pipes_redirs(redirs, ft_count_words((const char **)split));
		free_dbl_tab(split);
	}
	return (sig);
}

int	only_parenthesis(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (str_multi_cmp(split[i], "(", ")", NULL))
			return (0);
		i++;
	}
	return (1);
}

int	is_the_cmd_exist(char *cmd)
{
	if (!cmd)
		return (1);
	if (!str_multi_cmp(cmd, "alias", "bg", "bind", "break", "builtin", "caller",
			"cd", "command", "compgen", "complete", "compopt", "continue",
			"declare", "dirs", "disown", "echo", "enable", "eval", "exec",
			"exit", "export", "false", "fc", "fg", "getopts", "hash", "help",
			"history", "jobs", "kill", "let", "local", "logout", "popd",
			"printf", "pushd", "pwd", "read", "readonly", "return", "set",
			"shift", "shopt", "source", "suspend", "test", "times", "trap",
			"type", "typeset", "ulimit", "umask", "unalias", "unset", "wait",
			NULL))
		return (1);
	return (0);
}

char	*get_first_arg(char *av)
{
	char	*first_arg;
	int		i;

	if (!av)
		return (NULL);
	first_arg = malloc(sizeof(char) * (ft_strclen(av, ' ') + 1));
	if (!first_arg)
		return (printf("error : couldn't get first arg"), exit(1), NULL);
	i = 0;
	while (av[i] && av[i] != ' ')
	{
		first_arg[i] = av[i];
		i++;
	}
	first_arg[i] = 0;
	return (first_arg);
}
