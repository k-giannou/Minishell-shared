/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 15:27:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_charset(int c)
{
	char	*set;
	int		i;

	i = 0;
	set = " $  ' ";
	while (set[i] != '\0')
	{
		if (c == set[i++] || c == '\0' || c == '\"')
			return (1);
	}
	return (0);
}

void	handle_single(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];
	while (str[v->i] != '\'' && str[v->i] != '\0')
		v->line[v->k++] = str[v->i++];
	v->line[v->k++] = str[v->i++];
}

void	change_bools(t_variables *v, char *str)
{
	v->line[v->k++] = str[v->i++];
	v->quote_sum++;
	if (v->quote_sum % 2 == 0)
		v->dbl_quote = false;
	else
		v->dbl_quote = true;
}

void	ft_list_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

char	*replace_var(t_minishell *mini, char *str)
{
	t_env		*current;
	t_variables	v;

	if (!str)
		return (ft_exit(mini->tokens, mini), NULL);
	v = (t_variables){0};
	v = mini->vars;
	current = mini->env_export;
	if (!current)
		return (str);
	else
		start_replace(&v, str, mini, current);
	v.line[v.k] = '\0';
	free(str);
	str = NULL;
	str = ft_strdup(v.line);
	if (wildcars_exist_at(str, 0, true))
		str = handle_wildcards(str, mini);
	return (str);
}
