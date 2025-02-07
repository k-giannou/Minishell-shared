/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/07 15:04:50 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_env *env)
{
	char cwd[1024];

	while (ft_strncmp(env->data, "PWD=", 4))
		env = env->next;
	printf("%s\n", env->data + 4);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
    	printf("Répertoire courant : %s\n", cwd);
}
