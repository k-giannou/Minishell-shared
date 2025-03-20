/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiannou <kgiannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/20 16:01:32 by kgiannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_old_pwd(char *data, t_minishell **mini)
{
	t_env	*tmp;

	tmp = (*mini)->env;
	ft_get_env(&tmp, "OLDPWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("OLD", data);
	tmp = (*mini)->env_export;
	ft_get_env(&tmp, "OLDPWD=");
	free(tmp->data);
	tmp->data = ft_strjoin("OLD", data);
}

int	change_dir(char *str)
{
	struct stat	info;

	if (access(str, F_OK) == -1)
		return (g_signal = 1,
			ft_fprintf(2, "Error : Cannot access directory\n"));
	if (stat(str, &info) == -1)
		return (g_signal = 1,
			ft_fprintf(2, "Error : Cannot access infos of directory\n"));
	if (!S_ISDIR(info.st_mode))
		return (g_signal = 1,
			ft_fprintf(2, "minishell: cd: %s: Not a directory\n", str));
	if (chdir(str) == -1)
		return (g_signal = 1,
			ft_fprintf(2, "Error while changing repository\n"));
	return (0);
}

int	new_location(t_minishell **mini)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;

	tmp_env = (*mini)->env;
	ft_get_env(&tmp_env, "PWD=");
	if (!tmp_env)
		return (1);
	change_old_pwd(tmp_env->data, mini);
	free(tmp_env->data);
	tmp_env->data = ft_strjoin_n_free("PWD=", getcwd(NULL, 0), 2);
	if (!ft_strcmp(tmp_env->data, "PWD="))
		return (1);
	tmp_exp = (*mini)->env_export;
	ft_get_env(&tmp_env, "PWD=");
	if (!tmp_env)
		return (1);
	free(tmp_exp->data);
	tmp_exp->data = ft_strdup(tmp_env->data);
	return (0);
}

void	cd(char **path, t_minishell **mini)
{
	t_env		*tmp;
	char		*str;

	tmp = (*mini)->env;
	if (path[1] && path[2])
		return (g_signal = 1, \
	(void)ft_fprintf(2, "minishell: cd: too many arguments\n"));
	str = path[1];
	if (!path[1])
	{
		ft_get_env(&tmp, "HOME=");
		if (!tmp)
			return (g_signal = 1, \
	(void)ft_fprintf(2, "minishell: cd: HOME not set\n"));
		str = ft_strdup(tmp->data + 5);
	}
	if (change_dir(str))
		return ;
	(*mini)->cur_loc = replace_by_tilde((*mini)->env, (*mini)->cur_loc, 1);
	if (!(*mini)->cur_loc || new_location(mini))
		return (free_all(*mini, "all"), exit(1));
	g_signal = 0;
}
