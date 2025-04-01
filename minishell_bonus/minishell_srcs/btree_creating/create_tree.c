/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/01 19:53:18 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_right_branch_create_tree(t_btree **root, t_btree *to_add)
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

void	add_right_branch(t_btree **root, char **tokens, char **p_r, int *ptr_i)
{
	t_btree	*tmp;
	t_btree *to_add;

	to_add = right_branch(tokens, p_r, ptr_i);//i will create my right branch
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

void	build_right_branch(t_btree_params *p, char **tokens, char **p_r,
	t_btree **tree)
{
	t_btree	*right;
	int		j;

	if (!str_multi_cmp(p_r[p->i], "&&", "||", NULL))
		p->i++;
	j = 0;
	right = NULL;
	if (!ft_strcmp(p_r[p->i], "("))//if i have a parenthesis after
	{
		j = get_end_parenthesis(p_r, p->i, p->len_tokens);//i take the borders of my parenthesis
		p->i++;
		p->to_free++;//i want to free the duplicates
		add_right_branch_create_tree(&(*tree)->right,
			right_branch_par(*p, tokens, p_r, j));
		p->to_free--;
		p->i = j - 1;
	}
	else
		add_right_branch(&(*tree)->right, tokens, p_r, &p->i);//and add it to the main one
}

void	build_tree(t_btree_params p, char **tokens, char **p_r,
	t_btree **tree)
{
	int	j;
	
	p.i = 0;
	j = 0;
	while (p.i < p.len_tokens && tokens[p.i])
	{
		if (!*tree)
		{
			*tree = init_tree(p, tokens, p_r, 0);//the tree is perfect
			if (!*tree)//if it's perfectly NULL
				return ;//i return
			if (ft_strcmp(p_r[p.i], "("))
				p.i = go_to_op_log(p_r, p.i, p.len_tokens);
			else if (!ft_strcmp(p_r[p.i], "("))
				p.i = get_end_parenthesis(p_r, p.i, p.len_tokens);
		}
		if (!str_multi_cmp(p_r[p.i], "&&", "||", NULL)
			|| !get_next_oplog(tokens, p_r, p.i))//create the right branch and the left command if there's one
			build_right_branch(&p, tokens, p_r, tree);
		p.i++;
	}
}

t_btree	*create_tree(t_btree_params p, char **tokens, char **p_r)
{
	t_prior prior;
	t_btree *tree;

	tree = NULL;
	p.len_tokens = ft_count_words((const char **)tokens);
	set_symbols(tokens, p_r, &prior);
	if ((!prior.and && !prior.or))//if there's no shit
	{
		if (prior.parenthesis)
			remove_parenthesis(&tokens, &p_r, p.len_tokens);
		tree = btree_create_node(ft_splitdup(tokens),
			ft_splitndup(p_r, p.len_tokens, 0, p.len_tokens), CMD);
		if (p.to_free)
			multi_free("2, 2", tokens, p_r, NULL);
		return (tree);//i have one CMD
	}
	build_tree(p, tokens, p_r, &tree);
	if (p.to_free)
		multi_free("2, 2", tokens, p_r, NULL);
	return (tree);
}
