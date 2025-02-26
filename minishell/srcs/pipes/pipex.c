/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:14:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/26 17:48:40 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_arg(char *av)
{
	char *first_arg;
	int i;

	first_arg = malloc(sizeof(char) * (ft_strclen(av, ' ') + 1));
	if (!first_arg)
		return (printf("error : couldn't get first arg"), exit(1), NULL);
	i = -1;
	while (av[++i] && av[i] != ' ')
		first_arg[i] = av[i];
	first_arg[i] = 0;
	return (first_arg);
}

void	son_program(char *av, char **env, pid_t pid_son, t_minishell *mini)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror(RED "Error -> issue creating pipe\n" RESET), exit(1));//je creer mon pipe
	pid_son = fork();
	if (pid_son == -1)
		return (perror(RED "Error -> pid failure\n" RESET), exit(1));//je creer mon processus
	if (pid_son == 0)
	{
		close(fd[0]);//je ferme la lecture
		dup2(fd[1], STDOUT_FILENO);//je redirige la sortie standard dans l'ecriture du pipe
		if (is_buildin(get_first_arg(av), 1))
			exec_buildin(ft_split(av, " "), mini, 1);
		else
			execute(ft_strdup(av), env, mini);//j'execute a commande
		close(fd[1]);
		free_all(mini, "all");
		free_dbl_tab(env);
		free(av);
		exit(0);
	}
	close(fd[1]);//je ferme l'ecriture du pipe
	waitpid(pid_son, NULL, 0);//j'attends le processus enfant
	close(fd[0]);//je ferme la lecture
}

void	last_cmd(char *av, char **env, pid_t pid_son, t_minishell *mini)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror(RED "Error -> issue creating pipe\n" RESET), exit(1));//je creer mon pipe
	pid_son = fork();
	if (pid_son == -1)
		return (perror(RED "Error -> pid failure\n" RESET), exit(1));//je creer mon processus
	if (pid_son == 0)
	{
		close(fd[0]);//je ferme la lecture
		if (is_buildin(get_first_arg(av), 1))
			exec_buildin(ft_split(av, " "), mini, 1);
		else
			execute(ft_strdup(av), env, mini);//j'execute a commande
		close(fd[1]);
		free_all(mini, "all");
		free_dbl_tab(env);
		free(av);
		exit(0);
	}
	close(fd[1]);//je ferme l'ecriture du pipe
	waitpid(pid_son, NULL, 0);//j'attends le processus enfant
	close(fd[0]);//je ferme la lecture
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

char **get_cmd_s(t_minishell *mini, int i)
{
	int j;
	char **cmd_s;

	cmd_s = (char **)malloc(sizeof(char *) * (pipe_count(mini->tokens) + 2));
	if (!cmd_s)
		return (printf("fail getting cmd's"), NULL);
	j = 0;
	while (j < pipe_count(mini->tokens) + 1)
		cmd_s[j++] = NULL;
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
	cmd_s[++j] = NULL;
	return (cmd_s);
}

void	pipex(t_minishell *mini, char **env)
{
	int	i;
	char	**cmd_s;

	cmd_s = get_cmd_s(mini, 0);// je recupere un tableau de commandes a executer
	i = 0;
	while (i < ft_count_words(cmd_s) - 1)//tant que j'ai pas executer l'avant-derniere
		son_program(cmd_s[i++], env, 0, mini);//j'execute
	last_cmd(cmd_s[i], env, 0, mini);
	free_dbl_tab(cmd_s);
	free_dbl_tab(env);
}
