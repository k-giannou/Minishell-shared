/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 23:33:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_p_r(char **tokens, char **p_r, int j)
{
	int	i;

	i = j;
	i--;
	while (str_multi_cmp(p_r[i], "&&", "||", "(", ")", NULL)
		&& tokens[i] && i >= 0)
		i--;
	i++;
	return (ft_splitndup(p_r + i,
		ft_count_words((const char **)tokens + i), i, j));
}

char	*get_next_oplog(char **tokens, char **p_r, int i)
{
	while (str_multi_cmp(p_r[i], "&&", "||", "(", ")", NULL)
		&& tokens[i])
		i++;
	return (p_r[i]);
}

int	get_end_parenthesis(char **p_r, int i, int len_tokens)
{
	int	parenthesis_lvl;
	
	parenthesis_lvl = 1;
	while (parenthesis_lvl != 0 && i < len_tokens)
	{
		if (!ft_strcmp(p_r[i], "("))//if i have another opened parenthesis
			parenthesis_lvl++;
		else if (!ft_strcmp(p_r[i], ")"))//if i have another opened parenthesis
			parenthesis_lvl--;
		i++;
	}
	if (!parenthesis_lvl)
		return (i);
	else
		return (ft_fprintf(2, "minishell : error : parenthesis aren't closed"),
			ft_fprintf(2, " properly\n"), -1);
}

char	*get_and_or(char **tokens, char **p_r, int i)
{
	while (str_multi_cmp(p_r[i], "&&", "||", NULL)
		&& tokens[i])
		i++;
	return (p_r[i]);
}

t_btree *right_branch(char **tokens, char **p_r, int *i)
{
	t_btree	*cmd;
	t_btree	*logical_operator;

	cmd = btree_create_node(get_cmd_btree(tokens, p_r, i),
		get_p_r(tokens, p_r, *i), CMD);//i take the command
	if (!cmd)//if i don't have any command, there's a problem
		return (ft_fprintf(2, "minishell : error : no command after logical "),
			ft_fprintf(2, "operator\n"), NULL);
	if (!tokens[*i])//if i don't have any logical operators left
		return (cmd);//i return the command and put it to the right
	logical_operator = btree_create_node(ft_split(tokens[*i], NULL),
		ft_split(p_r[*i], NULL), get_type(tokens[*i]));
	logical_operator->left = cmd;
	return (logical_operator);//else i return the logical operator with the command on the left
}
