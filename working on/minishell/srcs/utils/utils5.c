/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/27 16:07:53 by locagnio         ###   ########.fr       */
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
