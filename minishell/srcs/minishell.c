/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:03:17 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 19:09:43 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//le bash doit fonctionner sur bash, pas zsh

t_env	*create_cell(char *data)
{
	t_env	*cell;

	cell = malloc(sizeof(t_env));
	if (!cell)
		return (NULL);
	cell->data = data;
	cell->next = NULL;
	return (cell);
}

void	init_env(t_env	**my_env, char **env)
{
	t_env	*tmp;
	int		i;
	char	*shlvl;

	i = 0;
	tmp = *my_env;
	shlvl = NULL;
	while (env[++i])
	{
		tmp->next = create_cell(ft_strdup(env[i]));
		tmp = tmp->next;
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			free(tmp->data);
			shlvl = ft_itoa(ft_atoi(env[i] + 6) + 1);
			tmp->data = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
		}
	}
}

int main(int ac, char **av, char **env)
{
	char		**line;
	t_minishell	*mini;
	
	(void)ac;
	(void)av;
	//welcome();
	mini = malloc(sizeof(t_minishell));
	mini->env = create_cell(env[0]);
	init_env(&(mini->env), env);
	while (1)
	{
		line = optimised_line(readline(YELLOW"minishell> "RESET), mini);
		if (line && line[0] && line[0][0] == 0)
			continue ;
		exec_cmd(line, mini);
	}
	free(line);
	return (0);
}
