/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:07:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 23:56:31 by marvin           ###   ########.fr       */
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
	if (tmp && !ft_strncmp(str, tmp->data + 5, ft_strlen(tmp->data + 5)))
	{
		new_str = ft_strjoin("~", str + ft_strlen(tmp->data + 5));
		free(str);
		return (new_str);
	}
	return (str);
}
