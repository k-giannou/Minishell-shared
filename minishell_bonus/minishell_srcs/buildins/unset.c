/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 15:43:11 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*free_at(t_env *L, int pos)
{
	t_env	*prec;
	t_env	*cur;
	int		i;

	cur = L;
	if (!L)
		return (NULL);
	else if (pos == 0)
	{
		L = L->next;
		free(cur);
		return (L);
	}
	i = 0;
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cur->next;
	free(cur);
	return (L);
}

void	delete_from_env(char *var, t_env **v)
{
	int		i;
	t_env	*temp;

	temp = *v;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->data, ft_strlen(var)) == 0)
		{
			if (i == 0 && !temp->next)
				*v = NULL;
			return (free(temp->data), (void)free_at(temp, i));
		}
		temp = temp->next;
		i++;
	}
}

void	unset(char **vars, t_minishell *mini)
{
	int	i;

	i = 1;
	if (just_export_or_unset(vars, "unset"))
		return ;
	while (vars[i])
	{
		if (!rest_letters_of_name(vars[i]))
			break ;
		delete_from_env(vars[i], &(mini->env));
		delete_from_env(vars[i], &(mini->env_export));
		i++;
	}
	mini->cur_loc = replace_by_tilde(mini->env_export, mini->cur_loc, 1);
	g_signal = 0;
}
