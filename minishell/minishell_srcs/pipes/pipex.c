/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/28 18:10:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_arg(char *av)
{
	char	*first_arg;
	int		i;

	if (!av)
		return (NULL);
	first_arg = malloc(sizeof(char) * (ft_strclen(av, ' ') + 1));
	if (!first_arg)
		return (printf("error : couldn't get first arg"), exit(1), NULL);
	i = 0;
	while (av[i] && av[i] != ' ')
	{
		first_arg[i] = av[i];
		i++;
	}
	first_arg[i] = 0;
	return (first_arg);
}

void	exec_child(char **env, t_minishell *mini, char **split, char **redirs)
{
	close_and_redirect_pipes(&mini->p, mini->p.i);
	if (isredir_pipex(mini->cmd_s[mini->p.i]))
	{
		split = ft_split(mini->cmd_s[mini->p.i], " ");
		redirs = get_redir_split(mini, mini->p.i);
		redir(mini, env, split, redirs);
		free_pipes_redirs(redirs, ft_count_words((const char **)split));
		free_dbl_tab(split);
	}
	else if (is_buildin(get_first_arg(mini->cmd_s[mini->p.i]), 1))
		exec_buildin(ft_split(mini->cmd_s[mini->p.i], " "), mini, 1);
	else
		execute(mini->cmd_s, env, mini);
	if (mini->p.i > 0)
		close(mini->p.pipes[mini->p.i - 1][0]);
	if (mini->p.pipes)
		free_pipes(mini->p.pipes, mini->p.nb_pipes);
	multi_free("2, 1, 2", mini->cmd_s, mini->p.pids, env, NULL);
	free_all(mini, "all");
	exit(0);
}

void	son_program(char **env, t_minishell *mini)
{
	mini->p.pids[mini->p.i] = fork();
	if (mini->p.pids[mini->p.i] == -1)
		return (perror(RED "Error -> pid failure\n" RESET));
	if (mini->p.pids[mini->p.i] == 0)
		exec_child(env, mini, NULL, NULL);
	else
		close_curr_pipe(&mini->p, mini->p.i, mini->cmd_s);
	if (mini->p.nb_pipes == 0)
		return ((void)waitpid(mini->p.pids[0], &g_signal, 0));
	if (mini->p.i == mini->p.nb_pipes)
		return ((void)waitpid(mini->p.pids[mini->p.i - 1], &g_signal, 0));
	mini->p.i++;
	son_program(env, mini);
	waitpid(mini->p.pids[mini->p.i - 1], NULL, 0);
}

char	**get_cmd_s(t_minishell *mini, int i)
{
	int		j;
	char	**cmd_s;

	if (!mini->tokens)
		return (NULL);
	cmd_s = (char **)ft_calloc(sizeof(char *), (mini->p.nb_pipes + 2));
	if (!cmd_s)
		return (printf("fail getting cmd's\n"), NULL);
	j = 0;
	while (mini->tokens[i])
	{
		if (!ft_strncmp(mini->pipes_redirs[i], "|", 1))
			j++;
		else
		{
			if (cmd_s[j])
				cmd_s[j] = ft_strjoin_n_free(cmd_s[j], " ", 1);
			cmd_s[j] = ft_strjoin_n_free(cmd_s[j], mini->tokens[i], 1);
		}
		i++;
	}
	return (cmd_s);
}

void	pipex(t_minishell *mini, char **env)
{
	int		i;

	i = -1;
	mini->p.nb_pipes = pipe_count(mini);
	mini->cmd_s = get_cmd_s(mini, 0);
	mini->p.i = 0;
	mini->p.pids = (pid_t *)ft_calloc(sizeof(pid_t), (mini->p.nb_pipes + 1));
	if (!mini->p.pids)
		return ((void)ft_fprintf(2, RED"Error : fail initiate pid's\n"RESET));
	if (mini->p.nb_pipes != 0)
		create_pipes(&mini->p);
	else
		mini->p.pipes = NULL;
	son_program(env, mini);
	free_pipes(mini->p.pipes, mini->p.nb_pipes);
	multi_free("2, 1, 2", mini->cmd_s, mini->p.pids, env, NULL);
}
