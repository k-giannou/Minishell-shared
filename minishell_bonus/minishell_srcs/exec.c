/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:25:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/27 17:50:21 by locagnio         ###   ########.fr       */
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
		if (tree->type == AND)
		ast(tree->right);
	}
	/* pipex(tree->data); */
}

void	print_btree(t_btree *root)
{
	if (root)
	{
		print_btree(root->left);
		ft_print_dlb_tabs(root->tokens, "tokens");
		print_btree(root->right);
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

t_btree *init_tree(char **tokens, char **p_r, int len_tokens)
{
	t_btree	*tree;
	int j;
	int incr;
	int parenthesis;

	j = 0;
	parenthesis = 0;
	tree = NULL;
	incr = 1;
	while (1)
	{
		while (str_multi_cmp(p_r[j], "&&", "||", NULL) && parenthesis != 0
			&& j < len_tokens)//while i didnt reach the end of parenthesis and a sign && or ||
		{
			if (!ft_strcmp(p_r[j], "("))
				parenthesis++;
			else if (!ft_strcmp(p_r[j], ")"))
				parenthesis--;
			j++;
		}
		if (j == len_tokens)//if a little fucker put a parenthesis on the whole lenght of the commands
		{
			len_tokens--;//i shorten the fucking scan by 1
			j = incr++;//motherfuckar
			if (len_tokens <= j)//if it's Gabriel and the whole shit is made of parenthesis, i return NULL
				return (ft_fprintf(2, "Bro, you're serious ?\n"), NULL);
		}
		else//if he or she is not a biche, i get out
			break;
	}
	if (!str_multi_cmp(p_r[j], "&&", "||", NULL) && (!j || !ft_strcmp(p_r[j - 1], "(")))//if i have a && or a || in the first string of right after an open parenthesis, i return NULL
		return (ft_fprintf(2, "minishell : logical operator at start of parenthesis\n"), NULL);
	else if (!str_multi_cmp(p_r[j], "&&", "||", NULL) && !tree)//else if my tree is empty
	{
		tree = btree_create_node(ft_split(p_r[j], NULL),
			ft_splitndup(p_r + j, 1, 0, 1), get_type(p_r[j]));//i create the first node with the operator
		tree->left = btree_create_node(ft_splitndup(tokens,
			ft_count_words((const char **)tokens), 0, j), ft_splitndup(p_r,
				ft_count_words((const char **)tokens), 0, j), CMD);//and the first command node
	}
	return (tree);
}

char	**get_cmd_btree(char **tokens, char **p_r, int *j)
{
	int		i;

	i = *j;
	(*j)++;
	while (str_multi_cmp(p_r[*j], "&&", "||", "(", ")", NULL)
		&& tokens[*j])
		(*j)++;
	return (ft_splitndup(tokens + i,
		ft_count_words((const char **)tokens + i), i, *j));
}

char	**get_p_r(char **tokens, char **p_r, int j)
{
	int		i;

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

t_btree	*left_branch_parenthesis(char **tokens, char **p_r, int parenthesis_lvl,
int *i)
{
	t_btree	*tree;
	int level_to_close;

	level_to_close = parenthesis_lvl - 1;
	tree = NULL;
	while (parenthesis_lvl > level_to_close)//while i didn't lower my level
	{
		if (!ft_strcmp(p_r[*i], "("))//if i have another opened parenthesis
		{
			(*i)++;
			parenthesis_lvl++;
			if (tree)//if i got something before
				tree->left = left_branch(tokens, p_r, parenthesis_lvl, i);//it goes on the left
			else
				tree = left_branch(tokens, p_r, parenthesis_lvl, i);//it becomes the tree
			break ;
		}
		else if (!ft_strcmp(p_r[*i], ")"))//if i've reached the end of a parenthesis
			parenthesis_lvl--;//i lower the lvl
		else if (!ft_strcmp(get_next_oplog(tokens, p_r, *i), ")"))//if the next logical operator is the parenthesis enclosure
			tree = btree_create_node(get_cmd_btree(tokens, p_r, i),
				get_p_r(tokens, p_r, *i), CMD);//i take the command
		else
			tree = btree_create_node(get_cmd_btree(tokens, p_r, i),
				get_p_r(tokens, p_r, *i), CMD);
	}
	return (tree);
}

t_btree *right_branch(char **tokens, char **p_r, int *i)
{
	t_btree *cmd;
	t_btree *logical_operator;

	cmd = btree_create_node(get_cmd_btree(tokens, p_r, i),
		get_p_r(tokens, p_r, *i), CMD);//i take the command
	if (!cmd)//if i don't have any command, there's a problem
		return (ft_fprintf(2, "minishell : error : no command after logical operator\n"));
	if (!tokens[*i])//if i don't have any logical operators left
		return (cmd);//i return the command and put it to the right
	logical_operator = btree_create_node(ft_split(tokens[*i], NULL),
		ft_split(p_r[*i], NULL), get_type(tokens[*i]));
	logical_operator->left = cmd;
	return (logical_operator);//else i return the logical operator with the command on the left
}

void	add_right_branch(t_btree **root, t_btree *to_add)
{
	t_btree *tmp;

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

t_btree *create_tree(t_minishell *mini, char **tokens, char **p_r, int len_tokens)
{
	t_btree	*tree;
	t_btree *right;
	int		i;
	int		j;

	tree = NULL;
	if ((!mini->prior.and && !mini->prior.or))//if there's no shit
		return (btree_create_node(ft_splitdup(tokens),
			ft_splitndup(p_r, len_tokens, 0, len_tokens), CMD));//i have one CMD
	i = 0;
	j = 0;
	tree = init_tree(tokens, p_r, len_tokens);//the tree is perfect
	if (!tree)//if it's perfectly NULL
		return (NULL);//i return
	while (tokens[i])
	{
		/* if (!ft_strcmp(p_r[i], "("))
		{
			mini->parenthesis_lvl++;
			tree->left = left_branch_parenthesis(tokens, p_r,
				mini->parenthesis_lvl, &i);
		}
		else */ if (!str_multi_cmp(p_r[i], "&&", "||", NULL) || !get_next_oplog(tokens, p_r, i))//if i have one of the signs
		{
			right = right_branch(tokens, p_r, &i);//i will create my right branch
			add_right_branch(&tree->right, right);//and add it to the main one
		}
		i++;
	}
	return (tree);
}

void	exec_cmd(t_minishell *mini)
{
	t_btree *btree;

	current_status(mini);
	btree = create_tree(mini, mini->tokens, mini->pipes_redirs,
		ft_count_words((const char **)mini->tokens));
	//print_btree(btree);
	//if (btree)
	//	ast(btree);
	free_all(mini, "tabs");
	mini->tokens = NULL;
	mini->pipes_redirs = NULL;
}
