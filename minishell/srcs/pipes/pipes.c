/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:25:23 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/19 17:21:52 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(int *fd, pid_t pid, t_minishell *mini)
{
	if (pipe(fd) == -1)
	{
		perror(RED "Error -> issue creating pipe\n" RESET);
		free_all(mini, "all");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(RED "Error -> pid failure\n" RESET);
		free_all(mini, "all");
		exit(EXIT_FAILURE);
	}
}

int	ispipe(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		if (!ft_strcmp(line[i++], "|"))
			return (1);
	return (0);
}

void	pipes(t_minishell *mini)
{
	int		status;
	pid_t	pid;
	int		fd[2];

	pid = 0;
	init_pipes(fd, pid, mini);
	status = 0;
	waitpid(pid, &status, 0);

	g_signal = WEXITSTATUS(status);
}