/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:03:42 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/20 16:51:55 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_and_change(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	char	*dest;

	current = mini->env;
	v->i++;
	v->t = 0;
	current = mini->env;
	while (ft_isalpha(str[v->i]) || ft_isnum(str[v->i]) || str[v->i] == '_')
		v->to_search[v->t++] = str[v->i++];
	v->to_search[v->t++] = '\0';
	dest = ft_strdup(v->to_search);
	while (current)
	{
		if (ft_strncmp(dest, current->data, ft_strlen(dest)) == 0)
		{
			while (current->data[v->t] != '\0')
				v->line[v->k++] = current->data[v->t++];
			break ;
		}
		current = current->next;
	}
	free(dest);
	dest = NULL;
}

int	handle_if_heredoc(t_variables *v, char *str)
{
	int	y;

	y = (v->i);
	if (y == 0)
		return (0);
	y--;
	while (y != 0 && ft_iswhitespace(str[y]))
		y--;
	if (y > 0 && str[y] == '<' && str[y - 1] == '<')
		return (1);
	return (0);
}

void	handle_question(t_variables *v)
{
	char	*num;

	v->i += 2;
	num = ft_itoa(g_signal);
	v->y = 0;
	while (num[v->y])
		v->line[v->k++] = num[v->y++];
	free (num);
	num = NULL;
}

void	handle_dollar(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	if (handle_if_heredoc(v, str))
		v->line[v->k++] = str[v->i++];
	else if (str[v->i + 1] == '\0' || str[v->i + 1] == 32 || str[v->i
			+ 1] == '$')
		v->line[v->k++] = str[v->i++];
	else if (str[v->i + 1] == '?')
		handle_question(v);
	else if (str[v->i + 1] == '\"' && v->dbl_quote)
		v->line[v->k++] = str[v->i++];
	else if ((str[v->i + 1] == '\"' || str[v->i + 1] == '\'')
		&& (!v->dbl_quote))
		v->i++;
	else if (ft_isalpha(str[v->i + 1]) || ft_isnum(str[v->i + 1])
		|| str[v->i + 1] == '_')
		search_and_change(v, str, mini, current);
	else
		v->line[v->k++] = str[v->i++];
}

void	start_replace(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	while (str[v->i] != '\0')
	{
		if (str[v->i] == '\'' && (!v->dbl_quote))
			handle_single(v, str);
		else if (str[v->i] == '\"')
			change_bools(v, str);
		else if (str[v->i] == '$')
			handle_dollar(v, str, mini, current);
		else
			v->line[v->k++] = str[v->i++];
	}
}
