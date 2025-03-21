/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 17:23:32 by locagnio         ###   ########.fr       */
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
// ((cmd1 && cmd2) || cmd3) || cmd4 && cmd5

void	handle_parenthesis(t_minishell *mini, int start, int end)
{
	int i;
	int open_p;

	i = 0 * start;
	open_p = 0;
	while (mini->pipes_redirs[end])
	{
		while (mini->pipes_redirs[end][i])
		{
			if (mini->pipes_redirs[end][i] == '(')
				open_p++;
			else if (mini->pipes_redirs[end][i] == ')')
				open_p--;
			if (open_p == 0)
				break ;
			i++;
		}
		if (open_p == 0)
			break ;
		end++;
		i = 0;
	}
}

void	ast(t_minishell *mini, int start, int end)
{
	bool	prior;

	if (!mini->prior.and && !mini->prior.or && !mini->prior.parenthesis)
		return (pipex(mini, splited_env(mini->env), 0,
				ft_count_words((const char **)mini->tokens)));
	if (mini->pipes_redirs[end][0] == '(')
		handle_parenthesis(mini, end, end);
	while (mini->tokens[end] && str_multi_cmp(mini->pipes_redirs[end],
			"||", "&&", NULL)
		&& mini->pipes_redirs[end][0] != '(')
		end++;
	if (mini->pipes_redirs[end][0] == '(' && mini->tokens[end + 1])
	{
		start = end + 1;
		while (mini->pipes_redirs[end][0] != ')')
		{
			if (!str_multi_cmp(mini->pipes_redirs[end], "||", "&&", NULL)
				&& mini->pipes_redirs[end][0] == '(')
				prior = true;
			end++;
		}
		if (prior == false)
			pipex(mini, splited_env(mini->env), start, end);
		else
			ast(mini, start, end);
	}
	else if (!ft_strcmp(mini->pipes_redirs[end], "&&")
		&& mini->tokens[end + 1])
	{
		start = end + 1;
		while ((mini->pipes_redirs[end] && mini->pipes_redirs[end][0] != ')')
			|| str_multi_cmp(mini->pipes_redirs[end], "||", "&&", NULL))
		{
			if (!str_multi_cmp(mini->pipes_redirs[end], "||", "&&", NULL)
				&& mini->pipes_redirs[end][0] == '(')
				prior = true;
			end++;
		}
		if (prior == false)
			pipex(mini, splited_env(mini->env), start, end);
		else
			ast(mini, start, end);
	}
	else if (!ft_strcmp(mini->pipes_redirs[end],
		"&&") && mini->tokens[end + 1])
	{
		start = end + 1;
		while ((mini->pipes_redirs[end] && mini->pipes_redirs[end][0] != ')')
			|| str_multi_cmp(mini->pipes_redirs[end], "||", "&&", NULL))
		{
			if (!str_multi_cmp(mini->pipes_redirs[end], "||", "&&", NULL)
				&& mini->pipes_redirs[end][0] == '(')
				prior = true;
			end++;
		}
		if (prior == false)
			pipex(mini, splited_env(mini->env), start, end);
		else
			ast(mini, start, end);
	}
}

void	exec_cmd(t_minishell *mini)
{
	current_status(mini);
	//ast(mini, 0, ft_count_words((const char **)mini->tokens));
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
