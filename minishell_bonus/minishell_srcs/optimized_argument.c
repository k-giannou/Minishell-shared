/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_argument.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:31:28 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 17:18:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_tokens(char *line, bool sgl_q, bool dbl_q, int i)
{
	int	count;

	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == SGL_Q || line[i] == DBL_Q)
			{
				valid_quotes(line[i++], &sgl_q, &dbl_q);
				while ((line[i] && sgl_q && line[i] != SGL_Q)
					|| (line[i] && dbl_q && line[i] != DBL_Q))
					i++;
				valid_quotes(line[i++], &sgl_q, &dbl_q);
			}
			while (line[i] && line[i] != SGL_Q && line[i] != DBL_Q
				&& line[i] != ' ')
				if_pipes_or_redirs(line, &i, &count);
		}
		count++;
	}
	return (count++);
}

static char	*ft_substr2(char *line, t_minishell **mini, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(*mini)->sgl_q = 0;
	(*mini)->dbl_q = 0;
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		if ((line[i] == SGL_Q || line[i] == DBL_Q) && !(*mini)->sgl_q
			&& !(*mini)->dbl_q)
			valid_quotes(line[i++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		if ((line[i] == SGL_Q && (*mini)->sgl_q) || (line[i] == DBL_Q
				&& (*mini)->dbl_q))
			valid_quotes(line[i++], &((*mini)->sgl_q), &((*mini)->dbl_q));
		else
			str[j++] = line[i++];
	}
	str[j] = 0;
	return (str);
}

static char	*ft_substr_mini(char *line, t_minishell **mini, int *new_i, int tab)
{
	int		len;
	char	c;

	len = 0;
	if (line[0] && ((line[0] == DBL_Q && line[1] == DBL_Q)
			|| (line[0] == SGL_Q && line[1] == SGL_Q)))
		return ((*mini)->pipes_redirs[tab] = return_tab(tab, new_i),
			return_tab(tab, new_i));
	if (!char_multi_cmp(line[len], '<', '>', '|', '&', '(', ')', 0))
	{
		c = get_multi_char_cmp(line[len], '<', '>', '|', '&', '(', ')', 0);
		if (c == '(' || c == ')')
			len++;
		else
			while (line[len] == c)
				len++;
	}
	else
		ft_substr_mini_2(line, mini, &len);
	*new_i += len;
	(*mini)->pipes_redirs[tab] = ft_substr_with_quotes(line, *mini, len);
	return (ft_substr2(line, mini, len));
}

void	split_line(char *line, t_minishell **mini, int i)
{
	int	j;

	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] != ' ')
		{
			(*mini)->tokens[j] = ft_substr_mini(line + i, mini, &i, j);
			if (!(*mini)->tokens[j])
				return (free_all(*mini, "tabs"));
			else if (!char_multi_cmp(line[i], '<', '>', '|', '&', '(', ')', 0)
				|| !char_multi_cmp((*mini)->tokens[j][0], '<', '>', '|', '&',
				'(', ')', 0))
				break ;
		}
		j++;
		while (line[i] == ' ')
			i++;
	}
	(*mini)->tokens[j] = NULL;
	(*mini)->pipes_redirs[j] = NULL;
}

void	optimised_line(char *line, t_minishell **mini)
{
	int	i;
	int	count;

	count = count_tokens(line, 0, 0, 0);
	(*mini)->tokens = malloc(sizeof(char *) * (count + 1));
	(*mini)->pipes_redirs = malloc(sizeof(char *) * (count + 1));
	if (!(*mini)->tokens || !(*mini)->pipes_redirs)
		return (free(line));
	i = 0;
	while (line[i] == ' ')
		i++;
	split_line(line + i, mini, 0);
	free(line);
}
