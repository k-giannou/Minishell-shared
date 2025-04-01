/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/01 19:22:28 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	current_status(char **tokens, char **p_r, t_prior prior)
{
	print_pipes_redirs(p_r,	ft_count_words((const char **)tokens));
	ft_print_dlb_tabs(tokens, "                   tokens");
	printf("\ncurrent stats :\n");
	printf("- nb of \""YELLOW"&&"RESET"\" = %d\n", prior.and);
	printf("- nb of \""GREEN"||"RESET"\" = %d\n", prior.or);
	printf("- nb of \""BLUE"|"RESET"\"  = %d\n", prior.pipes);
	printf("- nb of \""RED"()"RESET"\" = %d\n\n", prior.parenthesis);
}
// cmd4 && cmd5 || (cmd3 || (cmd1 && cmd2))

void	handle_parenthesis(t_minishell *mini, int start, int end)
{
	int	open_p;
	/* char **new_tokens;
	char **new_pipes_redirs; */

	open_p = 0 * start;
	while (mini->pipes_redirs[end])
	{
		if (!ft_strcmp(mini->pipes_redirs[end],"("))
			open_p++;
		else if (!ft_strcmp(mini->pipes_redirs[end],")"))
			open_p--;
		if (open_p == 0)
			break ;
		end++;
	}
	/* new_tokens = ft_splitndup(mini->tokens, ft_count_words(mini->tokens),
		start + 1, end);
	new_pipes_redirs = ft_splitndup(mini->pipes_redirs,
		ft_count_words(mini->tokens), start + 1, end);
	ast(new_tokens, new_pipes_redirs) */
}

void	print_btree(t_btree *root, int lvl, char *side)
{
	if (root)
	{
		print_btree(root->left, lvl + 1, "left");
		if (!ft_strcmp(side, "root"))
		{
			ft_fprintf(2, "\t      %s of the tree -> ", side);
			ft_print_dlb_tabs(root->tokens, "tokens");
		}
		else if (!ft_strcmp(side, "left"))
		{
			ft_fprintf(2, "lvl %d (%s  side) of the tree -> ", lvl, side);
			ft_print_dlb_tabs(root->tokens, "tokens");
		}
		else
		{
			ft_fprintf(2, "lvl %d (%s side) of the tree -> ", lvl, side);
			ft_print_dlb_tabs(root->tokens, "tokens");
		}
		print_btree(root->right, lvl + 1, "right");
	}
}

t_btree	*btree_create_node(char **item, char **p_r, int type)
{
	t_btree	*newnode;

	newnode = malloc(sizeof(t_btree));
	newnode->tokens = item;
	newnode->pipes_redirs = p_r;
	newnode->type = type;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}
//(cmd1 > file1 | cmd2 file1 && cmd3) || ((cmd4 cmd5 > file2)) && ((cmd6))
//display *(tokens + mini->i)@(len_tokens - mini->i)
//display *tokens@len_tokens
//display tokens[(*mini)->i]