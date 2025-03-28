/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 12:21:36 by kgiannou         ###   ########.fr       */
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
	while (line[*len] && char_multi_cmp(line[*len], ' ', '<', '>', '|', '&',
			'(', ')', 0))
	{
		if (line[*len] == SGL_Q || line[*len] == DBL_Q)
		{
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
			while ((line[*len] && (*mini)->sgl_q && line[*len] != SGL_Q)
				|| (line[*len] && (*mini)->dbl_q && line[*len] != DBL_Q))
				(*len)++;
			valid_quotes(line[(*len)++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		}
		while (line[*len] && char_multi_cmp(line[*len], SGL_Q, DBL_Q, ' ', '<',
				'>', '|', '&', '(', ')', 0))
			(*len)++;
	}
}

char	*get_cmd(char **av, int i)
{
	char	*cmd;

	if (!av || !av[i])
		return (NULL);
	cmd = ft_strdup(av[i++]);
	while (av[i] || str_multi_cmp(av[i], ">", ">>", "<", "<<", "|", "||", "&&",
			"(", ")", NULL))
		cmd = ft_strjoin_n_free(ft_strjoin_n_free(cmd, " ", 1), av[i++], 1);
	return (cmd);
}
