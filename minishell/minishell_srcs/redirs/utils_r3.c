/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:04 by kgiannou          #+#    #+#             */
/*   Updated: 2025/03/07 20:44:22 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_buildin(char **tab, t_minishell *mini, int free)
{
	if (!tab || !tab[0])
		return ;
	if (!ft_strcmp(tab[0], "pwd"))
		pwd();
	else if (!ft_strcmp(tab[0], "echo"))
		echo(tab);
	else if (!ft_strcmp(tab[0], "cd"))
		cd(tab, &mini);
	else if (!ft_strcmp(tab[0], "export"))
		export(tab, mini);
	else if (!ft_strcmp(tab[0], "unset"))
		unset(tab, mini);
	else if (!ft_strcmp(tab[0], "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(tab[0], "exit"))
		ft_exit(mini);
	if (free)
		free_dbl_tab(tab);
}
