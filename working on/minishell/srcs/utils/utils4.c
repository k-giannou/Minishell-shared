/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/24 18:39:45 by locagnio         ###   ########.fr       */
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

int	pipe_count(char **line)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
		if (!ft_strcmp(line[i++], "|"))
			count++;
	return (count);
}

void	ft_get_env(t_env **env, char *env_var)
{
	while (ft_strncmp((*env)->data, env_var, ft_strlen(env_var)))
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
	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
	{
		(*count)++;
		while (line[*i + 1] == '<' || line[*i + 1] == '>'
			|| line[*i + 1] == '|')
			(*i)++;
		if (line[*i + 1] != ' ')
			(*count)++;
	}
	(*i)++;
}
