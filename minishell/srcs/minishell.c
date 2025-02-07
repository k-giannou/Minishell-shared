/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:03:17 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 20:54:53 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//le bash doit fonctionner sur bash, pas zsh

char	*ft_readline(char *str)
{
	char	*line;

	ft_fprintf(1, "%s", str);
	line = get_next_line(0);
	line[ft_strlen(line) - 1] = 0;
	add_history(line);
	return (line);
}

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
			tmp->data = ft_strjoinm("SHLVL=", shlvl);
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
		line = optimised_line(ft_readline(YELLOW"minishell> "RESET), mini);
		if (!line || !line[0] || line[0][0] == 0)
			continue ;
		exec_cmd(line, mini);
	}
	free_dbl_tab(line);
	return (0);
}
