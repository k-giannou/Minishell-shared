/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/05 20:09:19 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	change_old_pwd(char *data, t_minishell **mini)
{
	t_env	*tmp;

	return ;
	tmp = (*mini)->env;
	ft_get_env(&tmp, "OLDPWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("OLD", data);
	tmp = (*mini)->env_export;
	ft_get_env(&tmp, "OLDPWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("OLD", data);
}

char	*new_location(t_minishell **mini, char *path, int i)
{
	t_env	*tmp;

	tmp = (*mini)->env;
	ft_get_env(&tmp, "PWD=");
	if (!tmp)
		return (NULL);
	change_old_pwd(tmp->data, mini);
	while (path && path[++i] && i < (int)ft_strlen(path))
	{
		if ((i == 0 && path[i] == '/'))
		{
			free(tmp->data);
			tmp->data = ft_strdup("PWD=/");
		}
		else if (!ft_strncmp(path + i, "../", 3) || !ft_strncmp(path + i,
				"..\0", 3))
		{
			new_location2(&tmp);
			i++;
		}
		else if (!ft_strncmp(path + i, "./", 2) || !ft_strncmp(path + i, ".\0",
				2))
			i++;
		else if (path[i + 1] != '.')
			add_directory(&tmp, path, &i);
	}
	return (g_signal = 0, tmp->data + 4);
}

void	cd(char **path, t_minishell **mini)
{
	struct stat	info;
	t_env		*tmp;
	char		*str;

	tmp = (*mini)->env;
	if (path[1] && path[2])
		return (g_signal = 0, (void)ft_fprintf(2, "bash: cd: too many arguments\n"));
	str = path[1];
	if (!path[1])
	{
		ft_get_env(&tmp, "HOME");
		if (tmp)
			str = ft_strdup(tmp->data + 5);
		else
			str = NULL;
	}
	if (access(str, F_OK) == -1)
		return (g_signal = 0, perror("Error "));
	if (stat(str, &info) == -1)
		return (g_signal = 0, perror("Error : Cannot acces to infos of directory\n"));
	if (!S_ISDIR(info.st_mode))
		return (g_signal = 0, (void)ft_fprintf(2, "bash: cd: %s: Not a directory\n", str));
	if (chdir(str) == -1)
		return (g_signal = 0, perror("Error while changing repository\n"));
	remove_multiple_slashs(str, 0);
	free((*mini)->cur_loc);
	(*mini)->cur_loc = new_location(mini, str, -1);
	tmp = (*mini)->env_export;
	ft_get_env(&tmp, "PWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("PWD=", (*mini)->cur_loc);
	(*mini)->cur_loc = replace_by_tilde((*mini)->env, (*mini)->cur_loc);
}
