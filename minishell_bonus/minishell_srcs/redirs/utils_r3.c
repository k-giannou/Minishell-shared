/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:04 by kgiannou          #+#    #+#             */
/*   Updated: 2025/04/03 17:34:06 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_buildin(char **tab, t_minishell *mini, int free)
{
	if (!tab || !tab[0])
		return ;
	if (!ft_strcmp(tab[0], "pwd"))
		pwd();
	else if (!ft_strcmp(tab[0], "echo"))
		echo(tab);
	else if (!ft_strcmp(tab[0], "cd"))
		cd(tab, &mini);
	else if (!ft_strcmp(tab[0], "export"))
		export(tab, mini);
	else if (!ft_strcmp(tab[0], "unset"))
		unset(tab, mini);
	else if (!ft_strcmp(tab[0], "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(tab[0], "exit"))
		ft_exit(mini);
	if (free)
		free_dbl_tab(tab);
}

void	handle_name_hr(char **pipes_redirs, char **tokens, int y)
{
	pipes_redirs[y] = ft_strdup("<");
	tokens[y] = ft_strdup("<");
	tokens[y++ + 1] = ft_strdup(".heredoc.txt");
}

void	path_and_execute(char *path, t_minishell *mini, char **env)
{
	path = find_path(mini->r.tab[0], env);
	if (!path)
	{
		restore_and_free(mini->r.tab, NULL, &mini->r);
		exit (-1);
	}
	if (execve(path, mini->r.tab, env) == -1)
	{
		restore_and_free(mini->r.tab, path, &mini->r);
		exit (-1);
	}
}

void	free_line(char **line)
{
	if (*line)
		free (*line);
	*line = NULL;
}
