/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/25 17:56:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_minishell *mini)
{
	if (!ft_strcmp(mini->tokens[0], "exit") && mini->p.nb_pipes == 0)
		ft_exit(mini);
	else
		pipex(mini, splited_env(mini->env));
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
