/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/21 10:26:32 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_minishell *mini, char **env)
{
	if (isredir(mini))
		redir(mini, env);
	/* if (ispipe(mini->tokens))
		pipes(mini);
	else  */else if (!ft_strcmp(mini->tokens[0], "pwd"))
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
		ft_fprintf(2, "%s: command not found\n", mini->tokens[0]);
	free_all(mini, "tabs");
}
