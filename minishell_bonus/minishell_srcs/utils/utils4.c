/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/05 21:08:09 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	set_symbols(char **tokens, char **p_r, t_prior *prior)
{
	int	i;
	int	len_split;

	i = 0;
	*prior = (t_prior){0};
	len_split = ft_count_words((const char **)tokens);
	while (i < len_split)
	{
		if (p_r[i])
		{
			if (!ft_strcmp(p_r[i], "|"))
				prior->pipes++;
			else if (!ft_strcmp(p_r[i], "||"))
				prior->or++;
			else if (!ft_strcmp(p_r[i], "&&"))
				prior->and++;
			else if (!ft_strcmp(p_r[i], "("))
				prior->parenthesis++;
		}
		i++;
	}
}

void	ft_get_env(t_env **env, char *env_var)
{
	while ((*env) && (*env)->data
		&& ft_strncmp((*env)->data, env_var, ft_strlen(env_var)))
		(*env) = (*env)->next;
}

int	first_letter_valid(char *str)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return (g_signal = 1, 0);
}

void	if_pipes_or_redirs(char *line, int *i, int *count)
{
	char	c;
	int		start;

	start = *i;
	c = 0;
	if (!char_multi_cmp(line[*i], '<', '>', '|', '&', '(', ')', 0))
	{
		(*count)++;
		c = get_multi_char_cmp(line[*i], '<', '>', '|', '&', '(', ')', 0);
		if ((c == '(' || c == ')') && line[*i + 1]
			&& char_multi_cmp(line[*i + 1], '<', '>', '|', '&', '(', ')', 0))
			(*count)++;
		/* else if ((c == '(' || c == ')') && !line[*i + 1])
			(*count)--; */
		else
		{
			while (line[*i] == c && !(c == '(' || c == ')'))
				(*i)++;
			if (start == 0 && !line[*i])
				(*count)--;
		}
	}
	if (*i < (int)ft_strlen(line))
		(*i)++;
}
