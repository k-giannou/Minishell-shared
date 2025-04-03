/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:42:30 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/03 17:08:49 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remv_par_while(char ***tokens, char ***p_r, int len_tokens, int i)
{
	int	j;

	j = i;
	while (!str_multi_cmp((*p_r)[j], "(", ")", NULL) && j < len_tokens)
	{
		free((*tokens)[j]);
		free((*p_r)[j]);
		j++;
	}
	while (j < len_tokens)
	{
		(*tokens)[i] = (*tokens)[j];
		(*p_r)[i] = (*p_r)[j];
		i++;
		j++;
	}
	while (i < len_tokens)
	{
		(*tokens)[i] = NULL;
		(*p_r)[i] = NULL;
		i++;
	}
}

void	remove_parenthesis(char ***tokens, char ***p_r, int len_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*tokens)[i] && i < len_tokens)
	{
		if (!str_multi_cmp((*p_r)[i], "(", ")", NULL))
		{
			remv_par_while(tokens, p_r, len_tokens, i);
			i = -1;
		}
		i++;
	}
}

int	go_to_op_log(char **p_r, int i, int len_tokens)
{
	while (str_multi_cmp(p_r[i], "&&", "||", "(", ")", NULL)
		&& i < len_tokens)
		i++;
	return (i);
}

t_btree	*right_branch_par(t_btree_params p, char **tokens, char **p_r, int j)
{
	t_btree	*cmd;
	t_btree	*logical_operator;
	int		len_tokens;

	len_tokens = ft_count_words((const char **)tokens);
	cmd = create_tree(p, ft_splitndup(tokens, len_tokens, p.i, j - 1),
			ft_splitndup(p_r, len_tokens, p.i, j - 1));
	if (!cmd || !cmd->tokens)
		return (ft_fprintf(2, "minishell : error : no command after logical "),
			ft_fprintf(2, "operator\n"), NULL);
	p.i = j;
	if (!tokens[p.i] || p.i >= len_tokens)
		return (cmd);
	logical_operator = btree_create_node(ft_split(tokens[p.i], NULL),
			ft_split(p_r[p.i], NULL), get_type(tokens[p.i]));
	logical_operator->left = cmd;
	p.i--;
	return (logical_operator);
}
