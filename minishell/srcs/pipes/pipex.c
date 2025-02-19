/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/15 18:17:57 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	son_program(char *av, char **env, pid_t pid_son)
{
	int	fd[2];
	int status;

	status = 0;
	if (pipe(fd) == -1)
	{
		perror(RED "Error -> issue creating pipe\n" RESET);
		exit(EXIT_FAILURE);
	}
	pid_son = fork();
	if (pid_son == -1)
	{
		perror(RED "Error -> pid failure\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (pid_son == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid_son, &status, 0);
		/* if (next cmd == NULL)
			g_signal = WEXITSTATUS(status); */
	}
}

int	get_file(char *av, int i)
{
	int	file;

	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		file = open(av, O_RDONLY);
	if (file == -1)
	{
		perror(RED "Error -> cannot open file\n" RESET);
		exit(EXIT_FAILURE);
	}
	return (file);
}

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror(RED "Error -> issue creating pipe\n" RESET);
		exit(EXIT_FAILURE);
	}
	reader = fork();
	if (reader == -1)
	{
		perror(RED "Error -> pid failure\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (reader == 0)
		read_stdin(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	pipex(int ac, char **av, t_minishell *mini)
{
	int	i;
	/* int	filein;
	int	fileout; */

	i = 1;
	/* fileout = get_file(av[ac - 1], 1);
	filein = get_file(av[1], 2);
	dup2(filein, STDIN_FILENO); */
	while (i < ac - 1)
		son_program(get_cmd(av, &i), splited_env(mini->env), 0);
	/* dup2(fileout, STDOUT_FILENO); */
	execute(av[ac - 2], splited_env(mini->env));
	return (0);
}
