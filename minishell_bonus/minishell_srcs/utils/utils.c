/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/14 19:45:51 by locagnio         ###   ########.fr       */
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

int	check_parenthesis(char **str, int j, int open_par, int close_par)
{
	int i;

	i = -1;
	while (str[j])
	{
		while (str[j][++i])
		{
			if (str[j][i] == '(')
				open_par++;
			else if (str[j][i] == ')')
				close_par++;
		}
		i = -1;
		j++;
	}
	if (open_par < close_par)
		ft_fprintf(2, "minishell: syntax error near unexpected token `)'\n");
	else if (open_par != close_par)
		return (ft_fprintf(2, "Error : parenthesis aren't closed properly\n"));
	return (0);
}

int	check_tokens_errors(char **raw, int i)
{
	if (!str_multi_ncmp(2, raw[i], "||", "&&", NULL)
		&& ((raw[i][2] && raw[i][3]) || i == 0
			|| (i > 0 && !str_multi_ncmp(1, raw[i - 1], "|", "&", NULL))))
		return (ft_fprintf(2, "minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%.2s'\n", raw[i]));
	else if ((i == 0 && !str_multi_cmp(raw[i], "|", "&", NULL)
		&& (!str_multi_ncmp(1, raw[i + 1], "|", "&", NULL))))
		return (ft_fprintf(2, "minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%c%c'\n",
				raw[i][0], raw[i + 1][0]));
	else if (i != 0 && !ft_strcmp(raw[i], "&"))
		return (ft_fprintf(2, "Error: Run commands in the background"),
			ft_fprintf(2, " is forbidden (\"&\")\n"));
	else if (!str_multi_ncmp(1, raw[i], "|", "&", NULL)
		&& ((raw[i][1] && char_multi_cmp(raw[i][1], '|', '&', 0)
			&& !raw[i][2]) || (raw[i][2] && !raw[i][3]) || i == 0))
		return (ft_fprintf(2, "minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%.1s'\n", raw[i]));
	else if (i > 0 && !str_multi_cmp(raw[i - 1], "||", "&&", "|", NULL)
		&& !str_multi_cmp(raw[i], "||", "&&", "|", NULL))
		return (ft_fprintf(2, "minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%s'\n", raw[i]));
	return (0);
}

int	is_symbols(char **raw, int i)
{
	if (check_parenthesis(raw, 0, 0, 0))
			return (1);
	i = -1;
	while (raw[++i])
		if (check_tokens_errors(raw, i))
			return (1);
	while (raw[--i] && i >= 0)
	{
		if (str_multi_cmp(raw[i], "<<", ">>", "<", ">", "&&", "||", "|", NULL)
			&& str_multi_ncmp(1, raw[i], "(", ")", NULL))
		{
			free(raw[i]);
			raw[i] = NULL;
		}
	}
	return (0);
}
