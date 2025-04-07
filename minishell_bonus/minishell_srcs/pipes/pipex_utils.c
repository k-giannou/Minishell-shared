/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:11:55 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/06 20:42:39 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**splited_env(t_env *env)
{
	int		i;
	char	**tab_env;

	if (!env)
		return (NULL);
	i = len_list(env);
	tab_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab_env)
		return (NULL);
	i = 0;
	while (env)
	{
		tab_env[i] = ft_strdup(env->data);
		if (!tab_env[i])
			return (free_dbl_tab(tab_env),
				printf("Error : changing env into split failed\n"), NULL);
		env = env->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

void	read_stdin(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
			exit(EXIT_SUCCESS);
		write(fd[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
}

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*possible_path;
	char	*path;

	i = 0;
	while (env[i] && ft_strnchr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ":");
	if (!paths)
		perror(RED "Error -> invalid path\n" RESET);
	i = 0;
	while (paths[i])
	{
		possible_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(path, F_OK) == 0 || access(path, X_OK) == 0)
			return (free_dbl_tab(paths), path);
		free(path);
		i++;
	}
	return (free_dbl_tab(paths), NULL);
}

char	*check_path(char **path, t_minishell *mini)
{
	t_env	*tmp;

	tmp = mini->env;
	if (!ft_strncmp(*path, "./", 2) || !ft_strncmp(*path, "../", 3))
	{
		ft_get_env(&tmp, "PWD=");
		*path = ft_strjoin_n_free(ft_strjoin(tmp->data + 4, "/"), *path, 1);
	}
	if (access(*path, F_OK) == 0 || access(*path, X_OK) == 0)
		return (ft_strdup(*path));
	return (NULL);
}

void	execute(char ***cmd, int i, char **env, t_minishell *mini)
{
	char	*path;

	free(mini->cmd_s_redirs);
	mini->cmd_s_redirs = NULL;
	if (!cmd[i])
		return (free_all(mini, "all"), free_dbl_tab(env),
			perror("Error -> issue spliting command\n"),
			free_pipes(mini->p.pipes, mini->p.nb_pipes), free(mini->p.pids),
			free_splits_array(&cmd), free_all(mini, "all"), exit(1));
	if (!(cmd[i][0][0] == '/' || !ft_strncmp(cmd[i][0], "./", 2)
		|| !ft_strncmp(cmd[i][0], "../", 2)))
		path = find_path(cmd[i][0], env);
	else
		path = check_path(&cmd[i][0], mini);
	if (!path)
		return (ft_fprintf(2, "%s: command not found\n", cmd[i][0]),
			free_pipes(mini->p.pipes, mini->p.nb_pipes), free_dbl_tab(env),
			free_splits_array(&cmd), free(mini->p.pids), free_all(mini, "all"),
			exit(127));
	if (execve(path, cmd[i], env) == -1)
	{
		free(path);
		perror("Error -> execution failure ");
	}
}
