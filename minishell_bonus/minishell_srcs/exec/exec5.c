/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:42:30 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/01 17:00:18 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remv_par_while(char ***tokens, char ***p_r, int len_tokens, int i)
{
	int j;

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
	int j;

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

t_btree *right_branch_par(t_minishell *mini, char **tokens, char **p_r, int j)
{
	t_btree	*cmd;
	t_btree	*logical_operator;
	int 	len_tokens;

	len_tokens = ft_count_words((const char **)tokens);
	cmd = create_tree(mini, ft_splitndup(tokens,
			len_tokens, mini->i, j - 1),
			ft_splitndup(p_r, len_tokens,
			mini->i, j - 1), NULL);//i take the command
	if (!cmd || !cmd->tokens)//if i don't have any command, there's a problem
		return (ft_fprintf(2, "minishell : error : no command after logical "),
			ft_fprintf(2, "operator\n"), NULL);
	mini->i = j;
	if (!tokens[mini->i] || mini->i >= len_tokens)//if i don't have any logical operators left
		return (cmd);//i return the command and put it to the right
	logical_operator = btree_create_node(ft_split(tokens[mini->i], NULL),
		ft_split(p_r[mini->i], NULL), get_type(tokens[mini->i]));
	logical_operator->left = cmd;
	(mini->i)--;
	return (logical_operator);//else i return the logical operator with the command on the left
}
