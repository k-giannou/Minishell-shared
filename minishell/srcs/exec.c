/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/28 20:06:57 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_splitdup_pipes_redirs(char **split, int len_split)
{
	char	**dup;
	int		i = 0;
	
	if (!split)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (len_split + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len_split)
	{
		dup[i] = split[i];
		if (!dup[i])
			return (free_dbl_tab(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	exec_cmd(t_minishell *mini)
{
	if (pipe_count(mini->tokens))
		pipex(mini, splited_env(mini->env));
	else if (isredir(mini))
		redir(mini, splited_env(mini->env), ft_splitdup(mini->tokens),
			ft_splitdup_pipes_redirs(mini->pipes_redirs,
				ft_count_words(mini->tokens)));
	else if (!ft_strcmp(mini->tokens[0], "pwd"))
		pwd(mini->env);
	else if (!ft_strcmp(mini->tokens[0], "echo"))
		echo(mini->tokens);
	else if (!ft_strcmp(mini->tokens[0], "cd"))
		cd(mini->tokens, &mini);
	else if (!ft_strcmp(mini->tokens[0], "export"))
		export(mini->tokens, mini);
	else if (!ft_strcmp(mini->tokens[0], "unset"))
		unset(mini->tokens, mini);
	else if (!ft_strcmp(mini->tokens[0], "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(mini->tokens[0], "exit"))
		ft_exit(mini);
	else
		pipex(mini, splited_env(mini->env));
	free_all(mini, "tabs");
}
