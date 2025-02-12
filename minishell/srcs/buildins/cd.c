/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 19:20:32 by locagnio         ###   ########.fr       */
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
		path[i++] = path[j++];//i copy the characters
	}
	ft_bzero(path + i, ft_strlen(path + i));
}

//je dois lire tout le chemin d'acces sauf si c'est un /
//je devrais modifier la chaine en annulant les entrees dans des fichiers avec les doubles
	//points correspondants, puis effectuer les changements ensuite
void	add_directory(t_env **tmp, char *path, int *i)
{
	char	str[257];
	int		j;

	j = 0;
	if (!ft_strcmp(path + *i, "/"))
		return ;
	ft_bzero(str, 257);
	str[j++] = '/';
	if (path[*i] == '/')
		(*i)++;
	while (path[*i] != '/')
		str[j++] = path[(*i)++];
	(*tmp)->data = ft_strjoin_n_free((*tmp)->data, ft_strdup(str), 12);		
}

char	*new_location(t_env *env, char *path, int i)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	while (ft_strncmp(tmp->data, "PWD", 3))
		tmp = tmp->next;
	str = NULL;
	while (path[++i])
	{
		if (i == 0 && path[i] == '/')
		{
			free(tmp->data);
			tmp->data = ft_strdup("/");
		}
		else if (!ft_strncmp(path + i, "../", 3) || !ft_strncmp(path + i, "..\0", 3))
		{
			str = tmp->data;
			tmp->data = ft_strndup(str, ft_strrchr(str, '/'));
			free(str);
			i++;
		}
		else
			add_directory(&tmp, path, &i);
	}
	return (tmp->data + 4);
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
	remove_multiple_slashs(path, 0);
	(*mini)->current_location = new_location((*mini)->env, path, -1);
	(*mini)->current_location = replace_by_tilde((*mini)->env, (*mini)->current_location);
}