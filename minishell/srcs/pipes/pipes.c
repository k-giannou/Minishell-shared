/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:25:23 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/15 15:34:11 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ispipe(char **line)
{
	int i;

	i = 0;
	while (line[i])
		if (!ft_strcmp(line[i++], "|"))
			return (1);
	return (0);
}

void	pipes(char **args)
{
	int status;

	status = 0;
	waitpid(pid, &status, 0);

	g_signal = WEXITSTATUS(status);
}