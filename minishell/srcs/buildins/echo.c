/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 21:04:06 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **line)
{
	int i;

	i = 1;
	if (!ft_strcmp(line[1], "-n"))
		i++;
	while (line[i])
	{
		ft_fprintf(1, "%s", line[i++]);
		if (line[i])
			ft_fprintf(1, " ");
	}
	if (ft_strcmp(line[1], "-n"))
		ft_fprintf(1, "\n");	
}
