/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:49:52 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/05 15:57:39 by locagnio         ###   ########.fr       */
=======
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:49:52 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/05 15:33:41 by kgiannou         ###   ########.fr       */
>>>>>>> 75fd9508efe331307b8f832369f89961c15a5834
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
	int		y;
	int		i;
	char	*tmp;

	y = 0;
	i = 0;
	while (i < ft_count_words(tokens))
	{
		if (tab[i])
		{
			if (i != y)
			{
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
<<<<<<< HEAD
	{
		if (to_free)
			free(tab);
		return (1);
	}
=======
		return (free(tab), 1);
>>>>>>> 75fd9508efe331307b8f832369f89961c15a5834
	if (to_free)
		free(tab);
	return (0);
}

int	isredir(t_minishell *mini)
{
	int	y;
	int	words;

	y = 0;
	words = ft_count_words(mini->tokens);
	while (y < words)
	{
		if (mini->pipes_redirs[y])
		{
			if (ft_strchr(mini->pipes_redirs[y], '>')
				|| ft_strchr(mini->pipes_redirs[y], '<')
				|| ft_strsrch(mini->pipes_redirs[y], ">>")
				|| ft_strsrch(mini->pipes_redirs[y], "<<"))
				return (1);
		}
		y++;
	}
	return (0);
}
