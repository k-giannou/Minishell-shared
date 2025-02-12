/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 17:40:13 by locagnio         ###   ########.fr       */
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
	str = tmp->data;
	len_path = ft_strlen(path);
	while ((path[i + 2] == '/' || path[i + 2] == 0)
		&& !ft_strncmp(path + i, "..", 2) && i < len_path)
	{
		str = tmp->data;
		tmp->data = ft_strndup(str, ft_strrchr(str, '/'));
		free(str);
		i += 3;
	}
	return (tmp->data);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}
/* char *optimised_path(char *path)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (path[++i])
	{
		if (!ft_strncmp(path + i, "../", 3) || !ft_strncmp(path + i, "..\0", 3))
		{
			j = i;
			if (j - 2 >= 0)
				j -= 2;
			else
				continue ;
			i += 2;
			while (path[j] != '/')
				j--;
			while (path[i - 1])
				path[j++] = path[i++];
			i = 0;	
		}
	}
	if (!ft_strchr(path, '/'))
		path = ft_strjoinm("/", path, 2);
	printf ("path = %s\n", path);
	return (path);
}

char	*new_location(t_env *env, char *path)
{
	t_env	*tmp;

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
		tmp->data = ft_strjoinm("PWD=", path, 0);
		return (tmp->data);
	}
	else if (path[ft_strlen(path) - 1] == '/')
		switch_slash(path, tmp->data + 4);
	tmp->data = ft_strjoinm(tmp->data, path, 1);
	return (tmp->data);
} */

//je dois lire tout le chemin d'acces sauf si c'est un /
//je devrais modifier la chaine en annulant les entrees dans des fichiers avec les doubles
	//points correspondants, puis effectuer les changements ensuite
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

char	*new_location(t_env *env, char *path, int i)
{
	t_env	*tmp;
	char	optimised_path[10000];

	tmp = env;
	while (ft_strncmp(tmp->data, "PWD", 3))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->data, "/"))
		return (free(tmp->data), (tmp->data = ft_strdup("/")));
	ft_bzero(optimised_path, 10000);
	while (path[++i])
	{
		if (!ft_strncmp(path + i, "../", 3) || !ft_strncmp(path + i, "..\0", 3))
		{
			if (!ft_strncmp(path + i, "../", 3) && path[i + 4]
				&& ft_strncmp(path + i + 3, "../", 3))
				
		}
	}
}

void	cd(char *path, t_minishell **mini)
{
	struct stat	info;

	if (access(path, F_OK) == -1)
		return (perror("Error "));
	if (stat(path, &info) == -1)
		return (perror("Error : Cannot acces to infos of directory\n"));
	if (!S_ISDIR(info.st_mode))
		return ((void)ft_fprintf(2, "bash: cd: %s: Not a directory\n", path));
	if (chdir(path) == -1)
		return (perror("Error while changing repository\n"));
	(*mini)->current_location = new_location((*mini)->env, optimised_path(path));
	printf("Repository changed successfully : %s\n", (*mini)->current_location);
}
