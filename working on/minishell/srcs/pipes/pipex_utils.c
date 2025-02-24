/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:11:55 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/22 18:23:28 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **av, int i)
{
	char *cmd;

	if (!av || !av[i])
		return (NULL);
	cmd = ft_strdup(av[i++]);
	while (av[i] || ft_strcmp(av[i], ">") || ft_strcmp(av[i], ">>")
			|| ft_strcmp(av[i], "<") || ft_strcmp(av[i], "<<")
			|| ft_strcmp(av[i], "|"))
		cmd = ft_strjoin_n_free(ft_strjoin_n_free(cmd, " ", 1), av[i++], 1);
	return (cmd);
}

char	**splited_env(t_env *env)
{
	int i;
	char **tab_env;
	
	i = len_list(env);
	tab_env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env)
	{
		tab_env[i++] = ft_strdup(env->data);
		env = env->next;
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

int	ft_words(const char *s, char c)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			sum++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (sum);
}

int	ft_fill(char **dest, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
		dest[i] = malloc(len + 1);
		if (!dest[i])
		{
			while (i)
				free (dest[--i]);
			free (dest);
			return (1);
		}
		ft_strlcpy(dest[i++], s - len, len + 1);
		while (*s == c && *s)
			s++;
	}
	dest[i] = 0;
	return (0);
}

char	**ft__split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	dest = (char **)malloc((ft_words(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	if (ft_fill(dest, s, c))
		return (NULL);
	return (dest);
}

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*possible_path;
	char	*path;

	(void)cmd;
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	//printf("path = %s\n", env[i]);
	paths = ft__split(env[i] + 5, ':');
	if (!paths)
		perror(RED "Error -> invalid path\n" RESET);
		
	i = 0;
	while (paths[i])
	{
		possible_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(possible_path, cmd);
		free(possible_path);
		//printf("paths = %s\n", paths[i]);	
		if (access(path, F_OK) == 0 || access(path, X_OK) == 0)
			return (free_dbl_tab(paths), path);
		free(path);
		i++;
	}
	free_dbl_tab(paths);
	return (0);
}

void	execute(char *av, char **env)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, " ");
	free(av);
	if (!cmd)
	{
		perror(RED "Error -> issue spliting command\n" RESET);
		exit(EXIT_FAILURE);
	}
	path = find_path(cmd[0], env);
	if (!path)
	{
		free_dbl_tab(cmd);
		perror(RED "Error -> issue finding path\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free_dbl_tab(cmd);
		perror(RED "Error -> execution failure\n" RESET);
		exit(EXIT_FAILURE);
	}
}
