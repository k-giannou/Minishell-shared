/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/04 17:50:42 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ast(t_minishell *mini, t_btree *the_tree)
{
	int	sig;

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
	t_prior	prior;
	int		len_tokens;

	set_symbols(mini->tokens, mini->pipes_redirs, &prior);
	if (is_buildin(mini->tokens[0], 0) && !prior.and && !prior.or
		&& !prior.pipes && !isredir(mini))
	{
		len_tokens = ft_count_words((const char **)mini->tokens);
		if (prior.parenthesis)
			remove_parenthesis(&mini->tokens, &mini->pipes_redirs, len_tokens);
		exec_buildin(mini->tokens, mini, 0, NULL);
	}
	else
	{
		btree = create_tree((t_btree_params){0}, mini->tokens,
				mini->pipes_redirs);
		if (btree)
			g_signal = ast(mini, btree);
		free_btree(btree);
	}
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}

	/* t_prior prior;

	set_symbols(mini->tokens, mini->pipes_redirs, &prior);
	current_status(mini->tokens, mini->pipes_redirs, prior); */
	//print_btree(btree, 1, "root");