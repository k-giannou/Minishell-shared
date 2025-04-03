/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/03 17:11:04 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_type(char *symbol)
{
	if (!symbol)
		return (0);
	if (!ft_strcmp(symbol, "||"))
		return (OR);
	else if (!ft_strcmp(symbol, "&&"))
		return (AND);
	else if (!str_multi_cmp(symbol, "(", ")", NULL))
		return (PARENTHESIS);
	else
		return (CMD);
}

int	get_log_op_check_par(char **p_r, int len_tokens, int *j, int incr)
{
	int	parenthesis;

	parenthesis = 0;
	while (1)
	{
		while ((str_multi_cmp(p_r[*j], "&&", "||", NULL) && *j < len_tokens)
			|| (parenthesis != 0))
		{
			if (!ft_strcmp(p_r[*j], "("))
				parenthesis++;
			else if (!ft_strcmp(p_r[*j], ")"))
				parenthesis--;
			(*j)++;
		}
		if (*j == len_tokens)
		{
			len_tokens--;
			*j = incr++;
			if (len_tokens <= *j)
				return (ft_fprintf(2, "Bro, you're serious ?\n"), 1);
		}
		else if (parenthesis == 0)
			break ;
	}
	return (0);
}

int	init_tree_error(char **p_r, int len_tokens, int *j)
{
	if (get_log_op_check_par(p_r, len_tokens, j, 0)
		|| (!str_multi_cmp(p_r[*j], "&&", "||", NULL)
			&& (!*j || !ft_strcmp(p_r[*j - 1], "("))))
		return (ft_fprintf(2, "minishell : logical operator at start of "),
			ft_fprintf(2, "parenthesis\n"), 1);
	return (0);
}

t_btree	*init_tree(t_btree_params p, char **tokens, char **p_r, int *j)
{
	t_btree	*tree;
	int		len_tokens;

	tree = NULL;
	len_tokens = ft_count_words((const char **)tokens);
	if (init_tree_error(p_r, len_tokens, j))
		return (NULL);
	else if (!str_multi_cmp(p_r[*j], "&&", "||", NULL))
	{
		tree = btree_create_node(ft_split(p_r[*j], NULL),
				ft_splitndup(p_r + *j, 2, 0, 1), get_type(p_r[*j]));
		if (!ft_strcmp(p_r[*j - 1], ")"))
		{
			p.to_free++;
			tree->left = create_tree(p, ft_splitndup(tokens, len_tokens, 1,
						*j - 1), ft_splitndup(p_r, len_tokens, 1, *j - 1));
			p.to_free--;
		}
		else
			tree->left = btree_create_node(ft_splitndup(tokens, len_tokens, 0,
						*j), ft_splitndup(p_r, len_tokens, 0, *j), CMD);
	}
	return (tree);
}

char	**get_cmd_btree(char **tokens, char **p_r, int *j)
{
	int	i;

	i = *j;
	(*j)++;
	while (str_multi_cmp(p_r[*j], "&&", "||", "(", ")", NULL)
		&& tokens[*j])
		(*j)++;
	return (ft_splitndup(tokens, ft_count_words((const char **)tokens), i, *j));
}
