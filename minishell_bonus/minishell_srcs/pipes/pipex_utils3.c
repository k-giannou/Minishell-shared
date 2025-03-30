/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 23:59:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**splited_env(t_env *env)
{
	int		i;
	char	**tab_env;

	if (!env)
		return (NULL);
	i = len_list(env);
	tab_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab_env)
		return (NULL);
	i = 0;
	while (env)
	{
		tab_env[i] = ft_strdup(env->data);
		if (!tab_env[i])
			return (free_dbl_tab(tab_env),
				printf("Error : changing env into split failed\n"), NULL);
		env = env->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

char	**get_redir_split(t_minishell *mini, int cur_cmd)
{
	int	start;
	int	end;
	int	nb_pipe;

	nb_pipe = 0;
	if (!mini->pipes_redirs || !mini->tokens)
		return (NULL);
	start = 0;
	while (nb_pipe < cur_cmd && mini->tokens[start])
	{
		if (!ft_strncmp(mini->tokens[start], "|", 1))
			nb_pipe++;
		start++;
	}
	end = start + 1;
	while (mini->tokens[end] && ft_strncmp(mini->tokens[end], "|", 1))
		end++;
	return (ft_splitndup(mini->pipes_redirs,
			ft_count_words((const char **)mini->tokens), start, end));
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
