/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/26 21:26:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_tab(int tab, int *new_i)
{
	if (tab == 0)
		return (*new_i += 2, ft_strdup("''"));
	else
		return (*new_i += 2, ft_strdup(""));
}

void	ft_substr_mini_2(char *line, t_minishell **mini, int *len)
{
	while (line[*len] && line[*len] != ' ' && line[*len] != '<'
		&& line[*len] != '>' && line[*len] != '|')
	{
		if (line[*len] == SGL_Q || line[*len] == DBL_Q)
		{
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
			while ((line[*len] && (*mini)->sgl_q && line[*len] != SGL_Q)
				|| (line[*len] && (*mini)->dbl_q && line[*len] != DBL_Q))
				(*len)++;
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		}
		while (line[*len] && line[*len] != SGL_Q && line[*len] != DBL_Q
			&& line[*len] != ' ' && line[*len] != '<' && line[*len] != '>'
			&& line[*len] != '|')
			(*len)++;
	}
}

char	**ft_splitndup(char **split, int len_split, int start, int end)
{
	char	**dup;
	int		i = 0;
	
	if (end > len_split)
		end = len_split;
	if (start > end || !split)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (end - start + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dup[i++] = split[start++];
		if (!dup[i - 1])
			return (free_dbl_tab(dup), NULL);
	}
	dup[i] = NULL;
	return (dup);
}
