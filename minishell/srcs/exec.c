/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/11 20:50:53 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **line, t_minishell *mini)
{
	if (!ft_strcmp(line[0], "pwd"))
		pwd(mini->env);
	else if (!ft_strcmp(line[0], "echo"))
			echo(line);
	else if (!ft_strcmp(line[0], "cd"))
		cd(line[1], &mini);
	/* else if (!ft_strcmp(line[0], "export"))
		return (1);
	else if (!ft_strcmp(line[0], "unset"))
		return (1);*/
	else if (!ft_strcmp(line[0], "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(line[0], "exit"))
		ft_exit(mini, line);
	else
		ft_fprintf(2, "%s: command not found\n", line[0]);
	free_all(NULL, line);
}
