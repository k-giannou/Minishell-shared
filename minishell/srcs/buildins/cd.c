/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/14 16:19:20 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	remove_multiple_slashs(char *path, int i)
{
	int j;

	j = 0;
	while (path[j])
	{
		if (path[i] == '/' && path[i + 1] == '/')//if there's multiple slashs
		{
			i++;//i keep the first slash
			while (path[j] == '/')//while i'm in the slashs
				j++;
		}
		if (i != j)
			path[i] = path[j];//i copy the characters
		i++;
		j++;
	}
	ft_bzero(path + i, ft_strlen(path + i));
}

void	add_directory(t_env **tmp, char *path, int *i)
{
	char	str[257];
	int		j;

	j = 0;
	ft_bzero(str, 257);
	if (ft_strcmp((*tmp)->data, "PWD=/"))
		str[j++] = '/';
	if (path[*i] == '/')
		(*i)++;
	while (path[*i] != '/' && path[*i])
		str[j++] = path[(*i)++];
	(*tmp)->data = ft_strjoin_n_free((*tmp)->data, ft_strdup(str), 12);		
}

void	new_location2(t_env **tmp)
{
	char	*str;

	str = (*tmp)->data;
	(*tmp)->data = ft_strndup(str, ft_strrchr(str, '/'));
	free(str);
	if (!ft_strcmp((*tmp)->data, "PWD="))
	{
		free((*tmp)->data);
		(*tmp)->data = ft_strdup("PWD=/");
	}
}

char	*new_location(t_env *env, char *path, int i)
{
	t_env	*tmp;

	tmp = env;
	ft_get_env(&tmp, "PWD=");
	while (path[++i] && i < (int)ft_strlen(path))
	{
		if ((i == 0 && path[i] == '/'))
		{
			free(tmp->data);
			tmp->data = ft_strdup("PWD=/");
		}
		else if (!ft_strncmp(path + i, "../", 3) || !ft_strncmp(path + i, "..\0", 3))
		{
			new_location2(&tmp);
			i++;
		}
		else if (!ft_strncmp(path + i, "./", 2) || !ft_strncmp(path + i, ".\0", 2))
			i++;
		else if (path[i + 1] != '.')
			add_directory(&tmp, path, &i);
	}
	return (tmp->data + 4);
}

void	cd(char *path, t_minishell **mini)
{
	struct stat	info;
	t_env		*tmp;

	if (!path)
		path = "/home/locagnio";
	if (access(path, F_OK) == -1)
		return (perror("Error "));
	if (stat(path, &info) == -1)
		return (perror("Error : Cannot acces to infos of directory\n"));
	if (!S_ISDIR(info.st_mode))
		return ((void)ft_fprintf(2, "bash: cd: %s: Not a directory\n", path));
	if (chdir(path) == -1)
		return (perror("Error while changing repository\n"));
	remove_multiple_slashs(path, 0);
	free((*mini)->current_location);
	(*mini)->current_location = new_location((*mini)->env, path, -1);
	tmp = (*mini)->env_export;
	ft_get_env(&tmp, "PWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("PWD=", (*mini)->current_location);
	(*mini)->current_location = replace_by_tilde((*mini)->env, (*mini)->current_location);
}
