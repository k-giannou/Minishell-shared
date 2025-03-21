/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/21 19:15:35 by locagnio         ###   ########.fr       */
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
// cmd4 && cmd5 || (cmd3 || (cmd1 && cmd2))

void	handle_parenthesis(t_minishell *mini, int start, int end)
{
	int open_p;
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
	new_pipes_redirs = ft_splitndup(mini->pipes_redirs, ft_count_words(mini->tokens),
		start + 1, end);
	ast(new_tokens, new_pipes_redirs) */
}

void	ast(t_btree *tree)
{
	if (tree->type != CMD)
	{
		ast(tree->left);
		if (tree->data == AND)
		ast(tree->right);
	}
	/* pipex(tree->data); */
}

void	print_btree(t_btree *root)
{
	if (root)
	{
		print_btree(root->left);
		printf("%s\n", root->data);
		print_btree(root->right);
	}
}

t_btree	*btree_create_node(char *item, int type)
{
	t_btree	*newnode;

	newnode = malloc(sizeof(t_btree));
	newnode->data = item;
	newnode->type = type;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}

t_btree *create_tree(t_minishell *mini)
{
	t_btree *tree;
	t_btree *tmp;
	
	tree = NULL;
	tree = btree_create_node("&&", AND);
	tree->left = btree_create_node("CMD1", CMD);
	tree->right = btree_create_node("CMD2", CMD);
	tmp = btree_create_node("||", OR);
	tmp->left = tree;
	tmp->right = btree_create_node("CMD3", CMD);
	tree = tmp;
	if (mini->prior.or)
	{
		
	}
	else if (mini->prior.and)
	{
		
	}
	/* else if (mini->prior.parenthesis)
	{
		
	}	 */
	return (tree);
}

void	exec_cmd(t_minishell *mini)
{
	t_btree *btree;

	//current_status(mini);
	btree = create_tree(mini);
	print_btree(btree);
	//ast(btree);
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
