/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 16:44:50 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_parenthesis(char **str, int j, int open_par, int close_par)
{
	int	i;

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
		return (ft_fprintf(2, "minishell: error : syntax error near \n"),
			ft_fprintf(2, "unexpected token `)'\n"));
	else if (open_par != close_par)
		return (ft_fprintf(2, "minishell: error : parenthesis aren't closed "),
			ft_fprintf(2, "properly\n"));
	return (0);
}

int	check_tokens_errors(char **raw, int i)
{
	if (!str_multi_ncmp(2, raw[i], "||", "&&", NULL)
		&& (!raw[i + 1] || (raw[i][2] && raw[i][3]) || i == 0
			|| (i > 0 && !str_multi_ncmp(1, raw[i - 1], "|", "&", NULL))))
		return (ft_fprintf(2, "1minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%.2s'\n", raw[i]));
	else if ((i == 0 && !str_multi_cmp(raw[i], "|", "&", NULL)
			&& (!str_multi_ncmp(1, raw[i + 1], "|", "&", NULL))))
		return (ft_fprintf(2, "2minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%c%c'\n",
				raw[i][0], raw[i + 1][0]));
	else if (i != 0 && !ft_strcmp(raw[i], "&"))
		return (ft_fprintf(2, "3minishell: error: Run commands in the "),
			ft_fprintf(2, "background is forbidden (\"&\")\n"));
	else if ((i > 0 && !ft_strcmp(raw[i - 1], "(") && !ft_strcmp(raw[i], ")"))
		|| (!str_multi_ncmp(1, raw[i], "|", "&", NULL)
		&& ((raw[i][1] && char_multi_cmp(raw[i][1], '|', '&', 0)
		&& !raw[i][2]) || (raw[i][2] && !raw[i][3]) || i == 0)))
		return (ft_fprintf(2, "4minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%.1s'\n", raw[i]));
	else if (i > 0 && !str_multi_cmp(raw[i - 1], "||", "&&", "|", NULL)
		&& !str_multi_cmp(raw[i], "||", "&&", "|", ")", NULL))
		return (ft_fprintf(2, "5minishell: syntax error"),
			ft_fprintf(2, " near unexpected token `%s'\n", raw[i]));
	return (0);
}

int	is_symbols(char **raw, int i)
{
	if (check_parenthesis(raw, 0, 0, 0) || only_parenthesis(raw))
		return (1);
	i = -1;
	while (raw[++i])
		if (check_tokens_errors(raw, i))
			return (1);
	i--;
	while (i >= 0 && raw[i])
	{
		if (str_multi_cmp(raw[i], "<<", ">>", "<", ">", "&&", "||", "|", NULL)
			&& str_multi_ncmp(1, raw[i], "(", ")", NULL))
		{
			free(raw[i]);
			raw[i] = NULL;
		}
		i--;
	}
	return (0);
}
