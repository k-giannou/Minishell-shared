/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/20 18:22:42 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_and_change(t_variables *v, char *str, t_minishell *mini,
		t_env *current)
{
	char	*dest;

	current = mini->env;
	v->i++;
	v->t = 0;
	current = mini->env;
	while (ft_isalpha(str[v->i]) || ft_isdigit(str[v->i]) || str[v->i] == '_')
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
		{
			if (str[v->i + 1] == '\0' || str[v->i + 1] == 32 || str[v->i
					+ 1] == '$')
				v->line[v->k++] = str[v->i++];
			else if (str[v->i + 1] == '\"' && v->dbl_quote)
				v->line[v->k++] = str[v->i++];
			else if ((str[v->i + 1] == '\"' || str[v->i + 1] == '\'')
				&& (!v->dbl_quote))
				v->i++;
			else if (ft_isalpha(str[v->i + 1]) || ft_isdigit(str[v->i + 1])
				|| str[v->i + 1] == '_')
				search_and_change(v, str, mini, current);
			else
				v->line[v->k++] = str[v->i++];
		}
		else
			v->line[v->k++] = str[v->i++];
	}
}

char	*replace_var(t_minishell *mini, char *str)
{
	t_env		*current;
	t_variables	v;

	if (!str)
		return (printf("exit\n"), exit(1), NULL);
	v = mini->vars;
	init_v(v);
	current = mini->env;
	if (!current)
		return (NULL);
	else
		start_replace(&v, str, mini, current);
	v.line[v.k] = '\0';
	free(str);
	return (ft_strdup(v.line));
}
