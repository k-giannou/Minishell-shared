/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/02 12:57:18 by kgiannou         ###   ########.fr       */
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

int	pipe_count(t_minishell *mini)
{
	int	i;
	int	count;
	int	len_split;

	i = 0;
	count = 0;
	len_split = ft_count_words((const char **)mini->tokens);
	while (i < len_split)
	{
		if (mini->pipes_redirs[i] && !ft_strncmp(mini->pipes_redirs[i], "|", 1))
			count++;
		i++;
	}
	return (count);
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
