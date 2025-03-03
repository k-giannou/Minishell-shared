/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:49:52 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/03 22:43:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_tokens(char **tokens)
{
	int		i;
	char	**tab_copy;

	i = ft_count_words(tokens);
	tab_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab_copy) 
	{
		perror("malloc failed");
		return (NULL);
	}
	i = 0;
	while (tokens[i])
	{
		tab_copy[i] = ft_strdup(tokens[i]);
		if (!tab_copy[i]) 
		{
			perror("strdup failed");
			free_dbl_tab(tab_copy);
			return (NULL);
		}
		i++;
	}
	tab_copy[i] = NULL;
	return (tab_copy);
}

void	join_command_free_tab(char **tab, char **tokens)
{
	int	y;
	int	i;
	
	y = 0;
	i = 0;
	while (i < ft_count_words(tokens))//correct null tabs between tokens because we free eof words
	{
		if (tab[i])
		{
			if (i != y)
			{
				char	*tmp;
				tmp = tab[i];
				tab[i] = tab[y];
				tab[y] = tmp;
			}
			y++;
		}
		i++;		
	}
}

void	find_tab(int *y, char **tnulls, char **tokens)
{

	while (tokens[*y])
	{
		if (!tnulls[*y])
			*y += 1;
		else
			break ;
	}
}

int	is_buildin(char *tab, int to_free)
{
	if (!ft_strcmp(tab, "pwd") || !ft_strcmp(tab, "echo")
		|| !ft_strcmp(tab, "cd") || !ft_strcmp(tab, "export")
		|| !ft_strcmp(tab, "unset") || !ft_strcmp(tab, "env")
		|| !ft_strcmp(tab, "exit"))
			return (free(tab), 1);
	if (to_free)
		free(tab);
	return (0);
}

void	exec_buildin(char **tab, t_minishell *mini, int free)
{
	if (!tab || !tab[0])
		return ;
	if (!ft_strcmp(tab[0], "pwd"))
		pwd(mini->env);
	else if (!ft_strcmp(tab[0], "echo"))
		echo(tab);
	else if (!ft_strcmp(tab[0], "cd"))
		cd(tab, &mini);
	else if (!ft_strcmp(tab[0], "export"))
		export(tab, mini);
	else if (!ft_strcmp(tab[0], "unset"))
		unset(tab, mini);
	else if (!ft_strcmp(tab[0], "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(tab[0], "exit"))
		ft_exit(mini);
	if (free)
		free_dbl_tab(tab);
}

int	isredir(t_minishell *mini)
{
	int	y;
	int	words;
	
	y = 0;
	words = ft_count_words(mini->tokens);
	while(y < words)
	{
		if (mini->pipes_redirs[y])
		{
			if (ft_strchr(mini->pipes_redirs[y], '>') || ft_strchr(mini->pipes_redirs[y], '<') 
			|| ft_strsrch(mini->pipes_redirs[y], ">>") || ft_strsrch(mini->pipes_redirs[y], "<<")) 
				return (1);
		}
		y++;
	}
	return (0);
}

void	restore_dup(t_redirs *r)
{
	if (r->saved_out != -1)
	{
		dup2(r->saved_out, STDOUT_FILENO);
		close(r->saved_out);
	}
	if (r->saved_in != -1)
	{
		dup2(r->saved_in, STDIN_FILENO);
		close(r->saved_in);
	}
}
