/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/19 20:54:44 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strsrch(const char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, c, ft_strlen(c)))
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

int		ispipe(char **line)
{
	int i;

	i = 0;
	while (line[i])
		if (!ft_strcmp(line[i++], "|"))
			return (1);
	return (0);
}