/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:46:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/07 19:33:36 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pipes(int **pipes, int nb_pipes)
{
	int	j;

	j = 0;
	while (j < nb_pipes)
		free(pipes[j++]);
	free(pipes);
}

void	free_pipes_redirs(char **str, int nb_words)
{
	int	j;

	j = 0;
	while (j < nb_words)
	{
		if (str[j])
			free(str[j]);
		j++;
	}
	if (str)
		free(str);
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
	begin_list = NULL;
}

void	free_all(t_minishell *mini, char *str)
{
	if (!ft_strcmp(str, "all") && mini)
	{
		if (mini->env)
			ft_list_clear(mini->env);
		if (mini->env_export)
			ft_list_clear(mini->env_export);
		if (mini->cur_loc)
			free(mini->cur_loc);
		if (mini->user.final)
			free(mini->user.final);
		if (mini->pipes_redirs)
			free_pipes_redirs(mini->pipes_redirs, ft_count_words(mini->tokens));
		if (mini->tokens)
			free_dbl_tab(mini->tokens);
		free(mini);
	}
	else if (!ft_strcmp(str, "tabs") && mini)
	{
		if (mini->pipes_redirs)
			free_pipes_redirs(mini->pipes_redirs, ft_count_words(mini->tokens));
		if (mini->tokens)
			free_dbl_tab(mini->tokens);
		mini->tokens = NULL;
		mini->pipes_redirs = NULL;
	}
}
