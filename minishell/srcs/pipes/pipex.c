/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/01 18:42:33 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_arg(char *av)
{
	char *first_arg;
	int i;

	if (!av)
		return (NULL);//motherfucker
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

void	exec_child(char **av, char **env, t_minishell *mini, int *fd)
{
	close(fd[0]);//i don't need lecture pipe
	if (mini->p.i < mini->p.nb_pipes)//if it's not the last pipe i redirect the output of the command into the pipe
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);//i close it
	if (is_buildin(get_first_arg(av[mini->p.i]), 1))//if it's buildin i execute it
		exec_buildin(ft_split(av[mini->p.i], " "), mini, 1);
	else
		execute(av, env, mini);//else i use execve
	free_all(mini, "all");
	free_dbl_tab(env);
	free_dbl_tab(av);
	exit(0);//i free everything and exit
}

int	son_program(char **av, char **env, t_minishell *mini)
{
	int	signal;
	int fd[2];

	signal = 0;
	if (pipe(fd) == -1)//I create a pipe
		return (perror(RED "Error -> issue creating pipe\n" RESET), 0);
	mini->p.pids[mini->p.i] = fork();//i create a fork
	if (mini->p.pids[mini->p.i] == -1)
		return (perror(RED "Error -> pid failure\n" RESET), 0);
	if (mini->p.pids[mini->p.i] == 0)//i go into the child process
		exec_child(av, env, mini, fd);
	close(fd[1]);//i don't need to write
	if (mini->p.i >= mini->p.nb_pipes)//if it's the last pipe
	{
		dup2(STDOUT_FILENO, fd[0]);
		waitpid(mini->p.pids[mini->p.i], &signal, 0);//i take the signal
		return(signal);//i return it
	}
	dup2(STDIN_FILENO, fd[0]);//else i redirect what's in the pipe in the standard input
	mini->p.i++;//i go to the next pipe and command
	signal += son_program(av, env, mini);//here we go again
	waitpid(mini->p.pids[mini->p.i - 1], NULL, 0);//i wait for every pipe when everything has been executed in the recursive
	return (signal);//i return the signal
}

char **get_cmd_s(t_minishell *mini, int i)
{
	int j;
	char **cmd_s;

	if (!mini->tokens)
		return (NULL);
	cmd_s = (char **)ft_calloc(sizeof(char *), (mini->p.nb_pipes + 2));
	if (!cmd_s)
		return (printf("fail getting cmd's\n"), NULL);
	j = 0;
	while (mini->tokens[i])
	{
		if (!ft_strcmp(mini->pipes_redirs[i], "|"))
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
	int j;

	mini->cmd_s = get_cmd_s(mini, 0);//i take the commands and their arguments together in a splited tab
	mini->p.i = 0;
	//redir(ft_split(cmd_s[i]), env);
	j = 0;
	mini->p.pids = (pid_t *)ft_calloc(sizeof(pid_t), (mini->p.nb_pipes + 1));//i malloc and initialise a string of process
	if (!mini->p.pids)
		return((void)ft_fprintf(2, RED"Error : fail initiate pipes or pid's\n"RESET));
	else
	{
		j = 0;
		g_signal = son_program(mini->cmd_s, env, mini);//i execute the pipes and get the last signal
		free(mini->p.pids);
	}
	free_dbl_tab(mini->cmd_s);
	free_dbl_tab(env);//i free everything
}
