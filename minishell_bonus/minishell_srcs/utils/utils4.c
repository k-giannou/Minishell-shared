/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/25 16:48:19 by locagnio         ###   ########.fr       */
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

void	set_symbols(t_minishell **mini)
{
	int	i;
	int	len_split;

	i = 0;
	(*mini)->prior = (t_prior){0};
	len_split = ft_count_words((const char **)(*mini)->tokens);
	while (i < len_split)
	{
		if ((*mini)->pipes_redirs[i])
		{
			if (!ft_strcmp((*mini)->pipes_redirs[i], "|"))
				(*mini)->prior.pipes++;
			else if (!ft_strcmp((*mini)->pipes_redirs[i], "||"))
				(*mini)->prior.or++;
			else if (!ft_strcmp((*mini)->pipes_redirs[i], "&&"))
				(*mini)->prior.and++;
			else if (!ft_strcmp((*mini)->pipes_redirs[i], "("))
				(*mini)->prior.parenthesis++;
		}
		i++;
	}
	ft_print_dlb_tabs((*mini)->tokens, "tokens");
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
	return (0);
}

void	if_pipes_or_redirs(char *line, int *i, int *count)
{
	char	c;

	c = 0;
	if (!char_multi_cmp(line[*i], '<', '>', '|', '&', '(', ')', 0))
	{
		(*count)++;
		c = get_multi_char_cmp(line[*i], '<', '>', '|', '&', '(', ')', 0);
		if (c == '(' || c == ')')
		{
			(*i)++;
			(*count)++;
		}
		else
			while (line[*i] == c)
				(*i)++;
		if (line[*i + 1] != ' ')
			(*count)++;
	}
	(*i)++;
}
