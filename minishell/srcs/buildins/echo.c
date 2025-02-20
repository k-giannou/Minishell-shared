/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/13 19:06:49 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_n(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	echo(char **line)
{
	int	i;

	i = 1;
	if (!line[i])
		return ((void)printf("\n"));
	while (line[i] && !ft_strncmp(line[i], "-n", 2))
	{
		if (echo_n(line[i]))
		{
			free(line[i]);
			line[i++] = ft_strdup("-n");
		}
		else
			break ;
	}
	while (line[i])
	{
		ft_fprintf(1, "%s", line[i++]);
		if (line[i])
			ft_fprintf(1, " ");
	}
	if (ft_strcmp(line[1], "-n"))
		printf("\n");
}
