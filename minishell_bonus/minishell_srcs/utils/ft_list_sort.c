/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:05:10 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 17:27:11 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	twenty_five_lines_bs(int *j, int *i, int *k)
{
	(*j)++;
	(*i)++;
	*k = *i;
}

int	will_exit(char **tokens)
{
	if (tokens && ft_strcmp(tokens[0], "exit"))
		return (0);
	if (tokens && tokens[0] && tokens[0][0]
		&& tokens[1] && (!valid_nb(tokens[1])
			|| strcmp_64_mini(
				ft_remove_from_string(tokens[1], " \n\v\f\r+", 0))))
		return (1);
	if (tokens && tokens[0] && tokens[0][0] && tokens[1]
		&& tokens[2])
		return (0);
	return (1);
}

static int	ft_sorted_list(t_env *list)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp && tmp->next)
	{
		while (tmp->data[i] && tmp->next->data[i])
		{
			if (tmp->data[i] > tmp->next->data[i])
				return (0);
			else if (tmp->data[i] < tmp->next->data[i])
				break ;
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
	return (1);
}

static void	ft_env_sort2(t_env **prev, t_env **cur, t_env **after)
{
	while (*after)
	{
		if (ft_strcmp((*cur)->data, (*after)->data) > 0)
		{
			(*cur)->next = (*after)->next;
			(*after)->next = *cur;
			(*prev)->next = *after;
			break ;
		}
		*prev = (*prev)->next;
		*cur = (*prev)->next;
		*after = (*cur)->next;
	}
}

void	ft_env_sort(t_env **begin_list)
{
	t_env	*prev;
	t_env	*cur;
	t_env	*after;

	while (!ft_sorted_list(*begin_list))
	{
		prev = *begin_list;
		cur = prev->next;
		after = cur->next;
		if (ft_strcmp(prev->data, cur->data) > 0)
		{
			prev->next = cur->next;
			cur->next = prev;
			*begin_list = cur;
			continue ;
		}
		ft_env_sort2(&prev, &cur, &after);
	}
}
