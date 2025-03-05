/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/04 17:41:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoinm(char *s1, char *s2, int tab_to_free)
{
	char	*new_string;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_string = ft_calloc(len, 1);
	if (!new_string)
		return (NULL);
	while (s1[++i] != '\0')
		new_string[i] = s1[i];
	while (s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	if (tab_to_free == 1)
		free(s1);
	else if (tab_to_free == 2)
		free(s2);
	else if (tab_to_free == 12)
		return (free(s1), free(s2), new_string);
	return (new_string);
}

char	*replace_by_tilde(t_env *env, char *str)
{
	int		i;
	int		j;
	char	*home;
	char	cpy[10000];

	i = 0;
	j = 0;
	ft_bzero(cpy, 10000);
	while (ft_strncmp(env->data, "HOME=", 5))
		env = env->next;
	home = env->data + 5;
	if (str && home && !ft_strncmp(str, home, ft_strlen(home)))
	{
		while (str[i] && home[i] && str[i] == home[i])
			i++;
		cpy[j++] = '~';
		while (str[i])
			cpy[j++] = str[i++];
		return (ft_strdup(cpy));
	}
	return (ft_strdup(str));
}

char	*ft_substr_with_quotes(char *line, t_minishell *mini, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mini->sgl_q = 0;
	mini->dbl_q = 0;
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (NULL);
	while (i < len)
		str[j++] = line[i++];
	str[j] = 0;
	return (str);
}

int	check_valid_quotes(char *str, bool *sgl_q, bool *dbl_q)
{
	int	j;

	j = 0;
	while (str[j])
	{
		valid_quotes(str[j], sgl_q, dbl_q);
		if (!*sgl_q && !*dbl_q && (str[j] == '|' || str[j] == '>'
				|| str[j] == '<'))
			return (1);
		j++;
	}
	return (0);
}

void	pipe_only(char **str, int i)
{
	int j;

	j = 0;
	while (str[i][j])
	{
		if (str[i][j++] != '|')
		{
			free(str[i]);
			str[i] = NULL;
			break ;
		}
	}
}


int	is_redir_or_pipes(char **raw, int i)
{
	while (raw[i])
	{
		if (raw[i][0] == '|')
			pipe_only(raw, i);
		else if (!((ft_strlen(raw[i]) == 2 &&
					(!ft_strcmp(raw[i], "<<") || !ft_strcmp(raw[i], ">>")))
					|| (ft_strlen(raw[i]) == 1 && (!ft_strcmp(raw[i], "<")
						|| !ft_strcmp(raw[i], ">")))))
		{
			free(raw[i]);
			raw[i] = NULL;
		}
		if (i > 0 && raw[i] && raw[i - 1] && raw[i][0] == '|'
			&& raw[i - 1][0] == '|')
			return (ft_fprintf(2, "bash: syntax error"),
				ft_fprintf(2, " near unexpected token `|'\n"));
		i++;
	}
	return (0);
}
