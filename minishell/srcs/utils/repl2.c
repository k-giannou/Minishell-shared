/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/20 17:27:35 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ftstrdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_charset(int c)
{
	char	*set;
	int		i;

	i = 0;
	set = " $  ' ";
	while (set[i] != '\0')
	{
		if (c == set[i++] || c == '\0' || c == '\"')
			return (1);
	}
	return (0);
}

void	init_v(t_variables v)
{
	v.dbl_quote = false;
	v.quote_sum = 0;
	v.i = 0;
	v.k = 0;
	v.t = 0;
}

void	handle_single(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];
	while (str[v->i] != '\'' && str[v->i] != '\0')
		v->line[v->k++] = str[v->i++];
	v->line[v->k++] = str[v->i++];
}

void	change_bools(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];
	v->quote_sum++;
	if (v->quote_sum % 2 == 0)
		v->dbl_quote = false;
	else
		v->dbl_quote = true;
}
