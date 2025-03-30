/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 22:49:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_by_tilde(t_env *env, char *str, int free_str)
{
	t_env	*tmp;
	char	*new_str;

	if (free_str)
		free(str);
	new_str = NULL;
	str = getcwd(NULL, 0);
	if (!str)
		return (ft_fprintf(2, "Error : unable to get the current directory\n"),
			NULL);
	tmp = env;
	ft_get_env(&tmp, "HOME=");
	if (tmp && !ft_strncmp(str, tmp->data + 5, ft_strlen(tmp->data + 5))
		&& tmp->data[ft_strlen(tmp->data) - 1] != '/')
	{
		new_str = ft_strjoin("~", str + ft_strlen(tmp->data + 5));
		free(str);
		return (new_str);
	}
	return (str);
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
	int	j;

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
		else if (str_multi_cmp(raw[i], "<<", ">>", "<", ">", NULL))
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
