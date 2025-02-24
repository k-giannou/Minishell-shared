/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/19 20:51:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	son_program(char *av, char **env, pid_t pid_son)
{
	int	fd[2];

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
		waitpid(pid_son, NULL, 0);
	}
}

void	get_file_nd_redir(char *av, int *filein, int *fileout)
{
	if (!ft_strcmp(av, ">"))
		*fileout = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (!ft_strcmp(av, ">>"))
		*fileout = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (!ft_strcmp(av, "<"))
		*filein = open(av, O_RDONLY);
	else if (!ft_strcmp(av, "<<"))
		*filein = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*filein == -1 || *fileout == -1)
	{
		perror(RED "Error -> cannot open file\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (*filein != STDIN_FILENO)
		dup2(*filein, STDIN_FILENO);
	if (*fileout != STDOUT_FILENO)
		dup2(*fileout, STDOUT_FILENO);
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

void	exec_redir(char *av, char **env, pid_t pid_son)
{
	int	fd[2];

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
		execute(av, env);
	}
	else
	{
		close(fd[1]);
		waitpid(pid_son, NULL, 0);
	}
}

int	pipex(char **av, char **env)
{
	int	i;
	int j;
	int	filein;//0
	int	fileout;//1

	i = 0;
	j = 0;
	filein = 0;
	fileout = 1;
	while (av[i])
	{
		if (!ft_strcmp(av[i], ">") || !ft_strcmp(av[i], ">>")
			|| !ft_strcmp(av[i], "<") || !ft_strcmp(av[i], "<<"))
		{
			get_file_nd_redir(av[i + 1], &filein, &fileout);
			j = i;
			while (j >= 0 || ft_strcmp(av[i], ">") || ft_strcmp(av[i], ">>")
			|| ft_strcmp(av[i], "<") || ft_strcmp(av[i], "<<")
			|| ft_strcmp(av[i], "|"))
				j--;
			exec_redir(get_cmd(av, j), env, 0);
		}
	}
	return (0);
}
