/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:00 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/10 19:16:46 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_quotes(char c, bool *sgl_q, bool *dbl_q)
{
	if (!(*sgl_q) && !(*dbl_q))
	{
		if (c == SGL_Q)
			(*sgl_q) = 1;
		else if (c == DBL_Q)
			(*dbl_q) = 1;
	}
	else if ((*sgl_q) || (*dbl_q))
	{
		if (c == SGL_Q && (*sgl_q) && !(*dbl_q))
			(*sgl_q) = 0;
		else if (c == DBL_Q && (*dbl_q) && !(*sgl_q))
			(*dbl_q) = 0;
	}
}

t_env	*add_at(t_env *L, char *data, int pos)
{
	t_env	*prec;
	t_env	*cur;
	int		i;
	t_cell	*cell;

	cur = L;
	cell = create_cell(data);
	if (!cell)
		return (NULL);
	if (!L)
		return (cell);
	else if (pos == 0)
	{
		cell->next = L;
		return (cell);
	}
	i = 0;
	while (i++ < pos)
	{
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (L);
}

t_env	*ft_envdup(t_env *src)
{
	t_env	*cpy;
	t_env	*tmp;
	int		i;

	tmp = src;
	i = 0;
	cpy = NULL;
	while (tmp)
	{
		cpy = add_at(cpy, ft_strdup(tmp->data), i);
		i++;
		tmp = tmp->next;
	}
	return (cpy);
}
