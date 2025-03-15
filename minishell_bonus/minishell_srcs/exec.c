/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:33:34 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/15 15:38:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	current_status(t_minishell *mini)
{
	print_pipes_redirs(mini->pipes_redirs,
		ft_count_words((const char **)mini->tokens));
	ft_print_dlb_tabs(mini->tokens, "                   tokens");
	printf("\ncurrent stats :\n");
	printf("- nb of \""YELLOW"&&"RESET"\" = %d\n", mini->prior.and);
	printf("- nb of \""GREEN"||"RESET"\" = %d\n", mini->prior.or);
	printf("- nb of \""BLUE"|"RESET"\"  = %d\n", mini->prior.pipes);
	printf("- nb of \""RED"()"RESET"\" = %d\n", mini->prior.parenthesis);
}

void	ast(t_minishell *mini)
{
	int i;
	
	i = 0;
	if (!mini->prior.and && !mini->prior.or && !mini->prior.parenthesis)
		pipex(mini, splited_env(mini->env), 0,
			ft_count_words((const char **)mini->env));
	/* while (mini->tokens) */
}

void	exec_cmd(t_minishell *mini)
{
	
	//current_status(mini);
	ast(mini);
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
