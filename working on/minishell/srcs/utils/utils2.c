/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:45:29 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/15 18:35:58 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_multiple_slashs(char *path, int i)
{
	int j;

	j = 0;
	while (path[j])
	{
		if (path[j] == '/' && path[j + 1] == '/')//if there's multiple slashs
		{
			i++;//i keep the first slash
			while (path[j] == '/')//while i'm in the slashs
				j++;
		}
		if (i != j)
			path[i] = path[j];//i copy the characters
		i++;
		j++;
	}
	ft_bzero(path + i, ft_strlen(path + i));
}

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

int	check_quotes(char *str)
{
	int i;
	bool sgl_q;
	bool dbl_q;

	if (!str)
		return (0);
	add_history(str);
	i = 0;
	sgl_q = 0;
	dbl_q = 0;
	while (str[i])
		valid_quotes(str[i++], &sgl_q, &dbl_q);
	if (sgl_q || dbl_q)
	{
		ft_fprintf(2, "Error : quotes aren't closed properly\n");
		free(str);
		return (1);
	}
	return (0);
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
