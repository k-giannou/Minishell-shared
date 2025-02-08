/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:03:17 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/08 17:27:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//le bash doit fonctionner sur bash, pas zsh

/* t_signal signal; */

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

int	init_env(t_env	**my_env, char **env)
{
	t_env	*tmp;
	int		i;
	char	*shlvl;

	i = 0;
	*my_env = create_cell(ft_strdup(env[i]));
	tmp = *my_env;
	shlvl = NULL;
	while (env[++i])
	{
		tmp->next = create_cell(ft_strdup(env[i]));
		if (!tmp->next)
			return (ft_list_clear(*my_env), 1);
		tmp = tmp->next;
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			free(tmp->data);
			shlvl = ft_itoa(ft_atoi(env[i] + 6) + 1);
			tmp->data = ft_strjoinm("SHLVL=", shlvl);
			free(shlvl);
			if (!tmp->data || !tmp->data[6])
				return (ft_list_clear(*my_env), 1);
		}
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	char		**line;
	t_minishell	*mini;
	
	(void)ac;
	(void)av;
	//welcome();
	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (ft_fprintf(2, "Error : fail init struct\n"), 1);
	if (init_env(&(mini->env), env))
		return (ft_fprintf(2, "Error : fail copying env\n"), 1);
	char *str = replace_var(mini, ft_readline(YELLOW"minishell> "RESET));
	while (ft_strcmp(str, "exit"))
	{
		if (!ft_strcmp(str, "env"))
			ft_env(mini->env);
		printf ("%s\n", str);
		free(str);
		str = ft_readline(YELLOW"minishell> "RESET);
	}
	/* while (1)
	{
		line = optimised_line(ft_readline(YELLOW"minishell> "RESET), mini);
		if (!line || !line[0] || line[0][0] == 0)
			continue ;
		exec_cmd(line, mini);
	} */
	line = NULL;
	free(str);
	free_all(mini, line);
	return (0);
}
