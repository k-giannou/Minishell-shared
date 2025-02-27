/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:49:52 by kgiannou          #+#    #+#             */
/*   Updated: 2025/02/26 20:40:09 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_tokens(char **tokens)
{
	int	i;
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


/* char **join_command_free_tab(char **tab, t_minishell *mini)
{
	int y;
	int	i;
	char	**new;

	y = 0;
	i = 0;
	while (mini->tokens[y])
	{
		if (tab[y] != NULL)
			i++;
		y++;
	}
	new = (char **)malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	y = 0;
	i = 0;
	while (mini->tokens[y])
	{
		if (tab[y] != NULL)
		{
			new[i++] = ft_strdup(tab[y]);
			free(tab[y]);
		}
		y++;
	}
	free(tab);
	tab = NULL;
	new[i] = NULL;
	return (new);
} */

void	join_command_free_tab(char **tab, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab || !tokens)
		return ;
	ft_print_dlb_tabs(tokens, "tokens");
	while (tokens && tokens[j] && j < ft_count_words(tokens))
	{
		while (!tab[j] && j < ft_count_words(tokens))
			j++;
		if (i != j)
			tab[i] = tab[j];
		i++;
		j++;
	}
	while (i < ft_count_words(tokens))
		tab[i++] = NULL;
	ft_print_dlb_tabs(tab, "tab");
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
			return (1);
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
