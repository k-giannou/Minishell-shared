/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/31 00:02:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_right_branch(t_btree **root, t_btree *to_add)
{
	t_btree	*tmp;

	if (!*root)//if i don't have any suite, it become my suite
	{
		*root = to_add;
		return ;
	}
	tmp = *root;//else, i go on the right until i can add the continuation
	while (tmp->right)
		tmp = tmp->right;
		tmp->right = to_add;
	}

t_btree	*create_tree3(t_minishell *mini, char **tokens, char **p_r,
	t_btree *tree)
{
	t_btree	*right;
	int		len_tokens;
	int		j;

	(*mini->ptr_i)++;
	j = 0;
	right = NULL;
	len_tokens = ft_count_words((const char **)tokens);
	if (!ft_strcmp(p_r[i], "("))//if i have a parenthesis after
	{
		(*mini->ptr_i)++;
		j = get_end_parenthesis(p_r, *mini->ptr_i, len_tokens);//i take the borders of my parenthesis
		mini->to_free++;//i want to free the duplicates
		tree->left = create_tree(mini, ft_splitndup(tokens,
			ft_count_words((const char **)tokens), 1, j - 1),
			ft_splitndup(p_r, ft_count_words((const char **)tokens),
			1, *j - 1), NULL);//i create my node
		mini->to_free--;
	}
	else
	{
		right = right_branch(tokens, p_r, mini->ptr_i);//i will create my right branch
		add_right_branch(&tree->right, right);//and add it to the main one
	}
}

t_btree	*create_tree2(t_minishell *mini, char **tokens, char **p_r,
	t_btree *tree)
{
	int	i;
	int	j;
	int	len_tokens;
	
	i = 0;
	mini->ptr_i = &i;
	j = 0;
	len_tokens = ft_count_words((const char **)tokens);
	while (tokens[i] && i < len_tokens)
	{
		if (!tree)
		{
			tree = init_tree(mini, tokens, p_r, len_tokens);//the tree is perfect
			if (!tree)//if it's perfectly NULL
				return (NULL);//i return
		}
		if (!str_multi_cmp(p_r[i], "&&", "||", NULL)
			|| !get_next_oplog(tokens, p_r, i))//create the right branch and the left command if there's one
			create_tree3(mini, tokens, p_r, tree);
		i++;
	}
}

t_btree	*create_tree(t_minishell *mini, char **tokens, char **p_r,
	t_btree *tree)
{
	int	len_tokens;

	len_tokens = ft_count_words((const char **)tokens);
	if ((!mini->prior.and && !mini->prior.or && !mini->prior.parenthesis))//if there's no shit
		return (btree_create_node(ft_splitdup(tokens),
			ft_splitndup(p_r, len_tokens, 0, len_tokens), CMD));//i have one CMD
	create_tree2(mini, tokens, p_r, tree);
	if (mini->to_free)
		multi_free("2, 2", tokens, p_r, NULL);
	return (tree);
}

void	exec_cmd(t_minishell *mini)
{
	t_btree	*btree;

	current_status(mini);
	btree = create_tree(mini, mini->tokens, mini->pipes_redirs, NULL);
	//print_btree(btree);
	//if (btree)
	//	ast(btree);
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
