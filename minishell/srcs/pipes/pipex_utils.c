/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:11:55 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/28 19:27:44 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd(char **av, int i)
{
	char	*cmd;

	if (!av || !av[i])
		return (NULL);
	cmd = ft_strdup(av[i++]);
	while (av[i] || ft_strcmp(av[i], ">") || ft_strcmp(av[i], ">>")
		|| ft_strcmp(av[i], "<") || ft_strcmp(av[i], "<<") || ft_strcmp(av[i],
			"|"))
		cmd = ft_strjoin_n_free(ft_strjoin_n_free(cmd, " ", 1), av[i++], 1);
	return (cmd);
}

char	**splited_env(t_env *env)
{
	int		i;
	char	**tab_env;

	if (!env)
		return (NULL);//retard shit
	i = len_list(env);
	tab_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab_env)
		return (NULL);
	i = 0;
	while (env)
	{
		tab_env[i] = ft_strdup(env->data);
		if (!tab_env[i])
			return (free_dbl_tab(tab_env), printf("Error : changing env into split failed\n"), NULL);
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
	free_dbl_tab(paths);
	return (0);
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

void	execute(char **av, char **env, t_minishell *mini)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av[mini->i], " ");
	free_dbl_tab(av);
	if (!cmd)
		return (free_all(mini, "all"), free_dbl_tab(env),
			perror(RED "Error -> issue spliting command\n" RESET), exit(1));
	if (!(cmd[0][0] == '/' || !ft_strncmp(cmd[0], "./", 2)	
		|| !ft_strncmp(cmd[0], "../", 2)))
		path = find_path(cmd[0], env);
	else
		path = check_path(&cmd[0], mini);
	if (!path)
		return (free_dbl_tab(cmd), free_all(mini, "all"), free_dbl_tab(env),
			perror(RED "Error -> issue finding path\n" RESET), exit(1));
	free_all(mini, "all");
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free_dbl_tab(env);
		free_dbl_tab(cmd);
		perror(RED "Error -> execution failure\n" RESET);
		exit(1);
	}
}
