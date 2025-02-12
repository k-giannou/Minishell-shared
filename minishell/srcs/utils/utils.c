/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:38:24 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 19:25:11 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoinm(char *s1, char *s2, int tab_to_free)
{
	char	*new_string;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_string = ft_calloc(len, 1);
	if (!new_string)
		return (NULL);
	while (s1[++i] != '\0')
		new_string[i] = s1[i];
	while (s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	if (tab_to_free == 1)
		free(s1);
	else if (tab_to_free == 2)
		free(s2);
	else if (tab_to_free == 12)
		return (free(s1), free(s2), new_string);
	return (new_string);
}

//str = /home/locagnio/common_git/minishell
//home = /home/locagnio
char	*replace_by_tilde(t_env *env, char *str)
{
	int i;
	char	*home;
	char	*tmp;

	i = 0;
	while (ft_strncmp(env->data, "HOME=", 5))
		env = env->next;
	home = env->data + 5;
	if (!ft_strncmp(str, home, ft_strlen(home)))
	{
		while (str[i] == home[i])
			i++;
		tmp = ft_strdup(str + i);
		return (ft_strjoin_n_free("~", tmp, 2));
	}
	return (str);
}
