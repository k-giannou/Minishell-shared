/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/11 21:15:40 by locagnio         ###   ########.fr       */
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

void	switch_slash(char *path)
{
	char	c;
	char	c2;
	int		i;

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

char	*new_location(t_env *env, char *path)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	while (ft_strncmp(tmp->data, "PWD", 3))
		tmp = tmp->next;
	if (!ft_strcmp(path, ".."))
	{
		str = tmp->data;
		printf ("%s\n", tmp->data);
		tmp->data = ft_strndup(str, ft_strrchr(str, '/'));
		printf ("%s\n", tmp->data);
		free(str);
		return (tmp->data);
	}
	switch_slash(path);
	printf ("%s\n", tmp->data);
	str = tmp->data;
	tmp->data = ft_strjoinm(str, path);
	printf ("%s\n", tmp->data);
	free(str);
	return (tmp->data);
}

void	cd(char *path, t_minishell **mini)
{
	struct stat	info;

	if (access(path, F_OK) == -1)
		return (perror("Erreur : Le répertoire n'existe pas"));
	if (stat(path, &info) == -1)
		return (perror("Erreur lors de l'accès aux informations du répertoire"));
	if (!S_ISDIR(info.st_mode))
		return ((void)ft_fprintf(2, "Erreur : Ce n'est pas un répertoire\n"));
	if (chdir(path) == -1)
		return (perror("Erreur lors du changement de répertoire"));
	(*mini)->current_location = new_location((*mini)->env, path);
	printf("Répertoire changé avec succès : %s\n", (*mini)->current_location);
}
