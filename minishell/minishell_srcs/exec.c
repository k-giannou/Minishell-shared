/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/25 18:06:47 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_minishell *mini)
{
	if (is_buildin(mini->tokens[0], 0)&& mini->p.nb_pipes == 0)
	{
		if (!ft_strcmp(mini->tokens[0], "exit"))
			ft_exit(mini);
		else if (!ft_strcmp(mini->tokens[0], "pwd"))
			pwd();
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
	}
	else
		pipex(mini, splited_env(mini->env));
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
