/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 15:04:37 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *src, int n)
{
	char	*cpy;
	int		i;

	i = 0;
	if (n > (int)ft_strlen(src))
		n = (int)ft_strlen(src);
	cpy = (char *)malloc(sizeof(char) * (n + 1));
	if (!cpy)
		return (NULL);
	while (src[i] && i < n)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (len);
		len--;
	}
	return (0);
}

void	switch_slash(char *path, char *curr_pwd)
{
	char	c;
	char	c2;
	int		i;

	if (!ft_strcmp(curr_pwd, "/"))
	{
		path[ft_strlen(path) - 1] = 0;
		return ;	
	}
	c = path[0];
	path[0] = '/';
	i = 0;
	while (path[++i])
	{
		c2 = path[i];
		path[i] = c;
		c = c2;
	}
}

char	*double_dots(t_env	*tmp, char *path)
{
	char	*str;
	int		i;
	int		len_path;

	i = 0;
	str = NULL;
	len_path = ft_strlen(path);
	while (str[i + 2] == '/' && !ft_strncmp(str + i, "..", 2)
		&& i < len_path)
	{
		str = tmp->data;
		tmp->data = ft_strndup(str, ft_strrchr(str, '/'));
		free(str);
		i += 3;
	}
	return (tmp->data);
}

char	*new_location(t_env *env, char *path)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	while (ft_strncmp(tmp->data, "PWD", 3))
		tmp = tmp->next;
	printf ("%s\n", tmp->data);
	if (!ft_strcmp(path, "."))
		return (tmp->data);
	if (!ft_strncmp(path, "..", 2))
		return (double_dots(tmp, path));
	if (path[0] == '/')
	{
		free(tmp->data);
		tmp->data = ft_strjoinm("PWD=", path);
		return (tmp->data);
	}
	else if (path[ft_strlen(path) - 1] == '/')
		switch_slash(path, tmp->data + 4);
	str = tmp->data;
	tmp->data = ft_strjoinm(str, path);
	free(str);
	return (tmp->data);
}

void	cd(char *path, t_minishell **mini)
{
	struct stat	info;

	if (access(path, F_OK) == -1)
		return (perror("Error "));
	if (stat(path, &info) == -1)
		return (perror("Error : Cannot acces to infos of repository\n"));
	if (!S_ISDIR(info.st_mode))
		return ((void)ft_fprintf(2, "Error : it's not a repository.\n"));
	if (chdir(path) == -1)
		return (perror("Error while changing repository\n"));
	(*mini)->current_location = new_location((*mini)->env, path);
	printf("Repository changed successfully : %s\n", (*mini)->current_location);
}
