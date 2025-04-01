/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/01 20:17:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ast(t_minishell *mini, t_btree *the_tree)
{
	int sig;

	sig = 0;
	if (the_tree->type == CMD)
		return (pipex(mini, the_tree, splited_env(mini->env)));
	if (the_tree->type == AND)
	{
		sig = ast(mini, the_tree->left);
		if (!sig)
			return (ast(mini, the_tree->right));
		else
			return (sig);
	}
	else if (the_tree->type == OR)
	{
		sig = ast(mini, the_tree->left);
		if (!sig)
			return (sig);
		else
			return (ast(mini, the_tree->right));
	}
	return (-1);
}

void	exec_cmd(t_minishell *mini)
{
	t_btree	*btree;
	/* t_prior prior;

	set_symbols(mini->tokens, mini->pipes_redirs, &prior);
	current_status(mini->tokens, mini->pipes_redirs, prior); */
	btree = create_tree((t_btree_params){0}, mini->tokens, mini->pipes_redirs);
	//print_btree(btree, 1, "root");
	if (btree)
		g_signal = ast(mini, btree);
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
