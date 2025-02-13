/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:54:19 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/13 21:04:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_dbl_tab(char **str)
{
	int	j;

	j = 0;
	while (str[j])
		free(str[j++]);
	if (str)
		free(str);
	str = NULL;
}

void	ft_list_clear(t_env *begin_list)
{
	t_env	*temp;

	temp = NULL;
	while (begin_list)
	{
		temp = begin_list->next;
		free(begin_list->data);
		free(begin_list);
		begin_list = temp;
	}
}

void	free_all(t_minishell *mini, char **str)
{
	if (mini)
	{
		if (mini->env)
			ft_list_clear(mini->env);
		if (mini->env_export)
			ft_list_clear(mini->env_export);
		if (mini->current_location)
			free(mini->current_location);
		free(mini);
	}
	if (*str)
		free_dbl_tab(str);
}
