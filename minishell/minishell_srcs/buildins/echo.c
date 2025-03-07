/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/05 18:04:07 by locagnio         ###   ########.fr       */
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
		return (g_signal = 0, (void)printf("\n"));
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
		printf("%s", line[i++]);
		if (line[i])
			printf(" ");
	}
	if (ft_strcmp(line[1], "-n"))
		printf("\n");
	g_signal = 0;
}
