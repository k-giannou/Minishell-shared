/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:25:54 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/20 18:26:35 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	init_v(t_variables v)
{
	v.dbl_quote = false;
	v.quote_sum = 0;
	v.i = 0;
	v.k = 0;
	v.t = 0;
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
